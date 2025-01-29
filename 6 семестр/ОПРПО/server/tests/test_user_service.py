from unittest.mock import Mock, AsyncMock, MagicMock
import pytest

from src.core.modules.service.user import UserService
from src.core.modules.database.errors import RepoNotFoundError, RepoAlreadyExistsError, RepoEmptyDataError
from src.core.modules.service.errors import UserNotFoundError, UserAlreadyExistsError, UserEmptyDataError
from src.models.user import UpdateUser

@pytest.mark.asyncio
async def test_get_all_users_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_all_users = AsyncMock(return_value=[{
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
    }])
    expected_id_1 = '60d5ec49f1a4a21f6c8b4567'
    expected_id_2 = '60d5ec49f1a4a21f6c8b4568'
    user_service = UserService(mock_repo)
    
    # Act
    result = await user_service.get_all_users()

    # Assert
    assert len(result) == 2
    assert int(result[0]["_id"], 16)
    assert int(result[1]["_id"], 16)
    assert result[0]['_id'] == expected_id_1
    assert result[1]['_id'] == expected_id_2


@pytest.mark.asyncio
async def test_get_all_users_fail():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_all_users.side_effect = Exception()

    user_service = UserService(mock_repo)
    try:
        # Act
        result = await user_service.get_all_users()
    except Exception as e:
        # Assert
        assert isinstance(e, Exception)


@pytest.mark.asyncio
async def test_get_user_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_user = AsyncMock(return_value={
        "_id": '60d5ec49f1a4a21f6c8b4567',
        "name": "Иван",
        "surname": "Иванов",
        "lastname": "Иванович",
        "email": "iiivanov@edu.ru",
        "position": "admin",
        "password": "sdfsdfwgesdgcx"
        })
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    user_service = UserService(mock_repo)
    
    # Act
    result = await user_service.get_user(expected_id)

    # Assert
    assert int(result["_id"], 16)
    assert result['_id'] == expected_id


@pytest.mark.asyncio
async def test_get_user_fail():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_user.side_effect = RepoNotFoundError()
    expected_id = '60d5ec49f1a4a21f6c8b4567'

    user_service = UserService(mock_repo)
    try:
        # Act
        result = await user_service.get_user(expected_id)
    except Exception as e:
        # Assert
        assert isinstance(e, UserNotFoundError)


@pytest.mark.asyncio
async def test_create_user_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.add_user = AsyncMock(return_value={
        "_id": '60d5ec49f1a4a21f6c8b4567',
        "name": "Иван",
        "surname": "Иванов",
        "lastname": "Иванович",
        "email": "iiivanov@edu.ru",
        "position": "regular",
        "password": "sdfsdfwgesdgcx"
        })
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    user_service = UserService(mock_repo)
    
    # Act
    result = await user_service.create_user({})

    # Assert
    assert int(result["_id"], 16)
    assert result['_id'] == expected_id
    assert result['position'] == 'regular'


@pytest.mark.asyncio
async def test_create_user_fail():
    # Arrange
    mock_repo = AsyncMock()
    mock_repo.add_user = AsyncMock(return_value=None)
    mock_repo.add_user.side_effect = RepoAlreadyExistsError()

    user_service = UserService(mock_repo)
    try:
        # Act
        result = await user_service.get_user({})
    except Exception as e:
        # Assert
        assert isinstance(e, UserAlreadyExistsError)


@pytest.mark.asyncio
async def test_update_user_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.update_user = AsyncMock(return_value={
        "_id": '60d5ec49f1a4a21f6c8b4567',
        "name": "Иван",
        "surname": "Иванов",
        "lastname": "Иванович",
        "email": "iiivanov@edu.ru",
        "position": "admin",
        "password": "sdfsdfwgesdgcx"
        })
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    user_service = UserService(mock_repo)
    
    # Act
    result = await user_service.update_user(expected_id, UpdateUser(
        name='Иван', position='admin', password='sdfsdfwgesdgcx', surname='Иванов', lastname='Иванович',
        email='iiivanov@edu.ru'))

    # Assert
    assert int(result["_id"], 16)
    assert result['_id'] == expected_id
    assert result['position'] == 'admin'


@pytest.mark.asyncio
async def test_update_user_fail_empty_data():
    # Arrange
    mock_repo = AsyncMock()
    mock_repo.add_user = AsyncMock(return_value=None)
    mock_repo.add_user.side_effect = RepoEmptyDataError()
    expected_id = '60d5ec49f1a4a21f6c8b4567'

    user_service = UserService(mock_repo)
    try:
        # Act
        result = await user_service.update_user(expected_id, UpdateUser(
        name='Иван', position='admin', password='sdfsdfwgesdgcx', surname='Иванов', lastname='Иванович',
        email='iiivanov@edu.ru'))
    except Exception as e:
        # Assert
        assert isinstance(e, UserEmptyDataError)


@pytest.mark.asyncio
async def test_update_user_fail_not_found():
    # Arrange
    mock_repo = AsyncMock()
    mock_repo.add_user = AsyncMock(return_value=None)
    mock_repo.add_user.side_effect = RepoNotFoundError()
    expected_id = '60d5ec49f1a4a21f6c8b4567'

    user_service = UserService(mock_repo)
    try:
        # Act
        result = await user_service.update_user(expected_id, UpdateUser(
        name='Иван', position='admin', password='sdfsdfwgesdgcx', surname='Иванов', lastname='Иванович',
        email='iiivanov@edu.ru'))
    except Exception as e:
        # Assert
        assert isinstance(e, UserNotFoundError)


@pytest.mark.asyncio
async def test_delete_user_success():
    # Arrange
    mock_repo = Mock()
    value_to_return = Mock()
    value_to_return.deleted_count = 1
    mock_repo.delete_user = AsyncMock(return_value=value_to_return)
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    user_service = UserService(mock_repo)
    
    # Act
    result = await user_service.delete_user(expected_id)

    # Assert
    assert result.deleted_count == 1


@pytest.mark.asyncio
async def test_delete_user_fail_not_found():
    # Arrange
    mock_repo = AsyncMock()
    mock_repo.delete_user = AsyncMock(return_value=None)
    mock_repo.delete_user.side_effect = RepoNotFoundError()
    expected_id = '60d5ec49f1a4a21f6c8b4567'

    user_service = UserService(mock_repo)
    try:
        # Act
        result = await user_service.delete_user(expected_id)
    except Exception as e:
        # Assert
        assert isinstance(e, UserNotFoundError)