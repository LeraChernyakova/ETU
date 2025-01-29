from unittest.mock import Mock
import pytest
from src.core.modules.database.statistics import MongoStatisticRepo
from src.models.filter import SessionFilter
from src.core.modules.database.errors import RepoNotFoundError


@pytest.mark.asyncio
async def test_get_all_sessions():
    # Arrange
    mock_client = Mock()
    mock_client.statistics.find.return_value.to_list.return_value = find_to_list()
    mock_filter = create_mock_filter()

    repository = MongoStatisticRepo(mock_client)
    
    # Act
    result = await repository.get_all_sessions(mock_filter)

    # Assert
    assert len(result) == 1
    assert result[0]["session_id"] == "2"


@pytest.mark.asyncio
async def test_get_session_success():
    # Arrange
    mock_client = Mock()
    record_id = '60d5ec49f1a4a21f6c8b4567'
    mock_client.statistics.find_one.return_value = find_one()

    repository = MongoStatisticRepo(mock_client)
    
    # Act
    result = await repository.get_session(record_id)

    # Assert
    assert result['_id'] == record_id


@pytest.mark.asyncio
async def test_add_session():
    # Arrange
    mock_client = Mock()
    record_id = '60d5ec49f1a4a21f6c8b4567'
    mock_client.statistics.insert_one.return_value = insert_one()
    mock_client.statistics.find_one.return_value = find_one()

    repository = MongoStatisticRepo(mock_client)
    
    # Act
    result = await repository.add_session({
        "actions": [
            {
                "action_type": "conversation",
                "element_html": "<input/>",
                "element_name": "сохранить",
                "element_type": "button",
                "event_type": "mousedown",
                "timestamp": "2024-05-20T19:13:13.056510"
            }
        ],
        "course": "Курс молодого бойца",
        "email": "iiivanov@edu.ru",
        "session_id": "60d5ec49f1a4a21f6c8b4567",
        "student": "Иванов Иван",
        "student_id": 1
    })

    # Assert
    assert result['_id'] == record_id


@pytest.mark.asyncio
async def test_delete_session_success():
    # Arrange
    mock_client = Mock()
    record_id = '60d5ec49f1a4a21f6c8b4567'
    mock_client.statistics.find_one.return_value = find_one()
    mock_client.statistics.delete_one.return_value = delete_one()

    repository = MongoStatisticRepo(mock_client)
    
    # Act
    result = await repository.delete_session(record_id)

    # Assert
    assert result.deleted_count == 1


@pytest.mark.asyncio
async def test_get_session_fail():
    # Arrange
    mock_client = Mock()
    record_id = '60d5ec49f1a4a21f6c8b4567'
    mock_client.statistics.find_one.side_effect = RepoNotFoundError()

    repository = MongoStatisticRepo(mock_client)
    try:
        # Act
        result = await repository.get_session(record_id)
    except Exception as e:
        # Assert
        assert isinstance(e, RepoNotFoundError)


@pytest.mark.asyncio
async def test_delete_session_fail():
    # Arrange
    mock_client = Mock()
    record_id = '60d5ec49f1a4a21f6c8b4567'
    mock_client.statistics.find_one.side_effect = RepoNotFoundError()

    repository = MongoStatisticRepo(mock_client)
    try:
        # Act
        result = await repository.delete_session(record_id)
    except Exception as e:
        # Assert
        assert isinstance(e, RepoNotFoundError)


def create_mock_filter():
    mock_filter = SessionFilter(end_timestamp=None)
    mock_filter.begin_timestamp = None
    mock_filter.student_id = None
    mock_filter.student_name = None
    mock_filter.student_email = None
    mock_filter.course_title = None
    mock_filter.action_type = None
    mock_filter.event_type = None
    mock_filter.element_type = None
    mock_filter.element_name = None
    return mock_filter


async def find_to_list():
    return [{
        "_id": "1", "session_id": "2", "actions": [{
            "timestamp": "2024-02-02T00:01",
            "element_type": "button",
            "element_name": "отправить",
            "action_type": "conversation",
            "event_type": "mousedown",
            "element_html": "<input/>"
        },
            {
                "timestamp": "2024-02-02T00:01",
                "element_type": "page",
                "element_name": "сохранить",
                "action_type": "hidden",
                "event_type": "visibilitychange",
                "element_html": "<input/>"
            }]
    }]


async def find_one():
    return {
        "_id": "60d5ec49f1a4a21f6c8b4567", "session_id": "2", "actions": [{
            "timestamp": "2024-02-02T00:01",
            "element_type": "button",
            "element_name": "отправить",
            "action_type": "conversation",
            "event_type": "mousedown",
            "element_html": "<input/>"
        },
            {
                "timestamp": "2024-02-02T00:01",
                "element_type": "page",
                "element_name": "сохранить",
                "action_type": "hidden",
                "event_type": "visibilitychange",
                "element_html": "<input/>"
            }]
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