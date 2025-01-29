from unittest.mock import Mock, MagicMock, AsyncMock
import pytest
from src.core.modules.database.user import MongoUserRepo
from src.core.modules.database.errors import (
    RepoNotFoundError, RepoEmptyDataError, RepoAlreadyExistsError)

@pytest.mark.asyncio
async def test_get_all_users():
    # Arrange
    mock_client = Mock()
    mock_client.users.find.return_value.to_list.return_value = get_all_users()
    expected_id_1 = '60d5ec49f1a4a21f6c8b4567'
    expected_id_2 = '60d5ec49f1a4a21f6c8b4568'
    user_repo = MongoUserRepo(mock_client)
    
    # Act
    result = await user_repo.get_all_users()

    # Assert
    assert len(result) == 2
    assert int(result[0]["_id"], 16)
    assert int(result[1]["_id"], 16)
    assert result[0]['_id'] == expected_id_1
    assert result[1]['_id'] == expected_id_2


@pytest.mark.asyncio
async def test_get_user_success():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one.return_value = get_user()
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    user_repo = MongoUserRepo(mock_client)
    
    # Act
    result = await user_repo.get_user(expected_id)

    # Assert
    assert int(result["_id"], 16)
    assert result['_id'] == expected_id


@pytest.mark.asyncio
async def test_delete_session_fail():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one.side_effect = RepoNotFoundError()
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    user_repo = MongoUserRepo(mock_client)

    try:
        # Act
        result = await user_repo.get_user(expected_id)
    except Exception as e:
        # Assert
        assert isinstance(e, RepoNotFoundError)


@pytest.mark.asyncio
async def test_get_user_by_email_success():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one.return_value = get_user()
    expected_email = 'iiivanov@edu.ru'
    user_repo = MongoUserRepo(mock_client)
    
    # Act
    result = await user_repo.get_user_by_email(expected_email)

    # Assert
    assert int(result["_id"], 16)
    assert result['email'] == expected_email


@pytest.mark.asyncio
async def test_get_user_by_email_fail_empty_data():
    # Arrange
    mock_client = Mock()
    expected_email = ''
    user_repo = MongoUserRepo(mock_client)

    try:
        # Act
        result = await user_repo.get_user_by_email(expected_email)
    except Exception as e:
        # Assert
        assert isinstance(e, RepoEmptyDataError)


@pytest.mark.asyncio
async def test_get_user_by_email_fail_not_found():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one.side_effect = RepoNotFoundError()
    expected_email = 'iiivanov@edu.ru'
    user_repo = MongoUserRepo(mock_client)

    try:
        # Act
        result = await user_repo.get_user_by_email(expected_email)
    except Exception as e:
        # Assert
        assert isinstance(e, RepoNotFoundError)


@pytest.mark.asyncio
async def test_add_user_success():
    mock_client = MagicMock()
    mock_collection = MagicMock()
    mock_client.users = mock_collection

    # Setting up the mock methods
    mock_collection.find_one = AsyncMock()
    mock_collection.insert_one = AsyncMock(
        return_value=MagicMock(inserted_id='60d5ec49f1a4a21f6c8b4567'))
    mock_collection.find_one.side_effect = [None, {
            "_id": '60d5ec49f1a4a21f6c8b4567',
            "name": "Иван",
            "surname": "Иванов",
            "lastname": "Иванович",
            "email": "iiivanov@edu.ru",
            "position": "admin",
            "password": "sdfsdfwgesdgcx"
        }]
    user_repo = MongoUserRepo(mock_client)

    # Test add_user
    result = await user_repo.add_user(create_mock_user_data())

    # Assertions
    assert result["email"] == "iiivanov@edu.ru"
    assert result["name"] == "Иван"
    assert "_id" in result
    assert result["_id"] == '60d5ec49f1a4a21f6c8b4567'
    

@pytest.mark.asyncio
async def test_add_user_fail_already_exists():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one = AsyncMock(return_value={})
    user_repo = MongoUserRepo(mock_client)

    try:
        # Act
        result = await user_repo.add_user(create_mock_user_data())
    except Exception as e:
        # Assert
        assert isinstance(e, RepoAlreadyExistsError)


@pytest.mark.asyncio
async def test_delete_user_success():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one.return_value = get_user()
    mock_client.users.delete_one.return_value = delete_one()
    id = '60d5ec49f1a4a21f6c8b4567'
    user_repo = MongoUserRepo(mock_client)
    
    # Act
    result = await user_repo.delete_user(id)

    # Assert
    assert result.deleted_count == 1


@pytest.mark.asyncio
async def test_delete_user_fail():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one = AsyncMock(return_value=None)
    id = '60d5ec49f1a4a21f6c8b4567'

    user_repo = MongoUserRepo(mock_client)
    try:
        # Act
        result = await user_repo.delete_user(id)
    except Exception as e:
        # Assert
        assert isinstance(e, RepoNotFoundError)


@pytest.mark.asyncio
async def test_update_user_success():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one = AsyncMock()
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    expected_name = 'Михаил'
    expected_role = 'regular'
    expected_user = await get_user()
    expected_user['name'] = expected_name
    expected_user['role'] = expected_role
    mock_client.users.find_one.side_effect = [await get_user(), expected_user]
    mock_client.users.update_one.return_value = update_user()

    user_repo = MongoUserRepo(mock_client)

    # Act
    result = await user_repo.update_user(expected_id, expected_user)
    # Assert
    assert result["_id"] == expected_id
    assert result['name'] == expected_name
    assert result['role'] == expected_role


@pytest.mark.asyncio
async def test_update_user_fail_empty_data():
    # Arrange
    mock_client = Mock()
    mock_client.users.find_one = AsyncMock(return_value=None)
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    expected_name = 'Михаил'
    expected_role = 'regular'
    expected_user = await get_user()
    expected_user['name'] = expected_name
    expected_user['role'] = expected_role

    user_repo = MongoUserRepo(mock_client)

    try:
        # Act
        result = await user_repo.update_user(expected_id, expected_user)
    except Exception as e:
        # Assert
        assert isinstance(e, RepoNotFoundError)


@pytest.mark.asyncio
async def test_update_user_fail_not_found():
    # Arrange
    mock_client = Mock()
    expected_id = '60d5ec49f1a4a21f6c8b4567'


    user_repo = MongoUserRepo(mock_client)
    try:
        # Act
        result = await user_repo.update_user(expected_id, {})
    except Exception as e:
        # Assert
        assert isinstance(e, RepoEmptyDataError)


async def get_all_users():
    return [{
        "_id": '60d5ec49f1a4a21f6c8b4567',
        "name": "Иван",
        "surname": "Иванов",
        "lastname": "Иванович",
        "email": "iiivanov@edu.ru",
        "position": "admin",
        "password": "sdfsdfwgesdgcx"
        }, {
        "_id": '60d5ec49f1a4a21f6c8b4568',
        "name": "Иван",
        "surname": "Иванов",
        "lastname": "Иванович",
        "email": "iiivanov@edu.ru",
        "position": "admin",
        "password": "sdfsdfwgesdgcx"
    }]

async def get_user():
    return {
            "_id": '60d5ec49f1a4a21f6c8b4567',
            "name": "Иван",
            "surname": "Иванов",
            "lastname": "Иванович",
            "email": "iiivanov@edu.ru",
            "position": "admin",
            "password": "sdfsdfwgesdgcx"
        }

def create_mock_user_data():
    return {
            "name": "Иван",
            "surname": "Иванов",
            "lastname": "Иванович",
            "email": "iiivanov@edu.ru",
            "position": "admin",
            "password": "sdfsdfwgesdgcx"
        }

def update_mock_user_data():
    return {
        "name": "Иван",
        "surname": "Иванов",
        "lastname": "Иванович",
        "email": "iiivanov@edu.ru",
        "position": "regular",
        "password": "sdfsdfwgesdgcx"
    }

    
async def insert_one():
    class CreatedSession:
        def __init__(self):
            self.inserted_id = "60d5ec49f1a4a21f6c8b4567"
            self.id = "60d5ec49f1a4a21f6c8b4567"
    return CreatedSession()

async def delete_one():
    class DeletedSession:
        def __init__(self):
            self.deleted_count = 1
    return DeletedSession()


async def update_user():
    return True
