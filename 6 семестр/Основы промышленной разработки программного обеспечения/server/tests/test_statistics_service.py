from unittest.mock import Mock
import pytest
from src.core.modules.service.statistics import StatisticsService, SessionFilter
from src.core.modules.database.errors import RepoNotFoundError
from src.core.modules.service.errors import SessionNotFoundError


@pytest.mark.asyncio
async def test_get_all_sessions_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_all_sessions.return_value = repo_get_all_sessions()

    service = StatisticsService(mock_repo, None)
    
    # Act
    result = await service.get_all_sessions(SessionFilter())

    # Assert
    assert len(result) == 1
    assert int(result[0]["_id"], 16)
    assert result[0]["_id"] == "60d5ec49f1a4a21f6c8b4567"
    assert result[0]["session_id"] == "2"


@pytest.mark.asyncio
async def test_get_all_sessions_fail():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_all_sessions.side_effect = RepoNotFoundError()

    service = StatisticsService(mock_repo, None)
    
    try:
        # Act
        result = await service.get_all_sessions(SessionFilter())
    except Exception as e:
        # Assert
        assert isinstance(e, RepoNotFoundError)


@pytest.mark.asyncio
async def test_get_session_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_session.return_value = repo_get_session()
    expected_id = '60d5ec49f1a4a21f6c8b4567'

    service = StatisticsService(mock_repo, None)
    
    # Act
    result = await service.get_session("60d5ec49f1a4a21f6c8b4567")

    # Assert
    assert int(result['_id'], 16)
    assert result['_id'] == expected_id


@pytest.mark.asyncio
async def test_get_session_fail():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_session.side_effect = RepoNotFoundError()

    service = StatisticsService(mock_repo, None)
    
    try:
        # Act
        result = await service.get_session("60d5ec49f1a4a21f6c8b4567")
    except Exception as e:
        # Assert
        assert isinstance(e, SessionNotFoundError)


@pytest.mark.asyncio
async def test_delete_session_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.delete_session.return_value = repo_delete_session()

    service = StatisticsService(mock_repo, None)
    
    # Act
    result = await service.delete_session("60d5ec49f1a4a21f6c8b4567")

    # Assert
    assert result.deleted_count == 1


@pytest.mark.asyncio
async def test_delete_session_fail():
    # Arrange
    mock_repo = Mock()
    mock_repo.delete_session.side_effect = RepoNotFoundError()

    service = StatisticsService(mock_repo, None)
    
    try:
        # Act
        result = await service.delete_session("60d5ec49f1a4a21f6c8b4567")
    except Exception as e:
        # Assert
        assert isinstance(e, SessionNotFoundError)


@pytest.mark.asyncio
async def test_create_session_success():
    # Arrange
    mock_repo = Mock()
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    mock_session_data = create_mock_session_data()
    mock_repo.add_session.return_value = repo_add_session()

    service = StatisticsService(mock_repo, None)
    
    # Act
    result = await service.create_session(mock_session_data)

    # Assert
    assert result['_id'] == expected_id


@pytest.mark.asyncio
async def test_create_session_fail():
    # Arrange
    mock_repo = Mock()
    mock_session_data = create_mock_session_data()
    mock_repo.create_record.side_effect = Exception()

    service = StatisticsService(mock_repo, None)
    
    try:
        # Act
        result = await service.create_session(mock_session_data)
    except Exception as e:
        # Assert
        assert isinstance(e, Exception)


@pytest.mark.asyncio
async def test_create_page_success():
    # Arrange
    mock_page = Mock()
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    mock_page_data = create_mock_page_data()
    mock_page.create_record.return_value = repo_create_page()

    service = StatisticsService(None, mock_page)
    
    # Act
    result = await service.create_page(mock_page_data)

    # Assert
    assert result['_id'] == expected_id


@pytest.mark.asyncio
async def test_create_page_fail():
    # Arrange
    mock_page = Mock()
    mock_page_data = create_mock_page_data()
    mock_page.create_record.side_effect = Exception()

    service = StatisticsService(None, mock_page)
    
    try:
        # Act
        result = await service.create_page(mock_page_data)
    except Exception as e:
        # Assert
        assert isinstance(e, Exception)


@pytest.mark.asyncio
async def test_get_pages_success():
    # Arrange
    mock_page = Mock()
    expected_id_1 = '60d5ec49f1a4a21f6c8b4567'
    expected_id_2 = '60d5ec49f1a4a21f6c8b4568'
    mock_page.get_all_records.return_value = repo_get_all_records()

    service = StatisticsService(None, mock_page)
    
    # Act
    result = await service.get_pages()

    # Assert
    assert len(result) == 2
    assert int(result[0]["_id"], 16)
    assert int(result[1]["_id"], 16)
    assert result[0]['_id'] == expected_id_1
    assert result[1]['_id'] == expected_id_2


@pytest.mark.asyncio
async def test_get_pages_fail():
    # Arrange
    mock_page = Mock()
    mock_page.get_all_records.side_effect = Exception()

    service = StatisticsService(None, mock_page)
    
    try:
        # Act
        result = await service.get_pages()
    except Exception as e:
        # Assert
        assert isinstance(e, Exception)


async def repo_get_all_sessions():
    return [{
        "_id": "60d5ec49f1a4a21f6c8b4567", 
        "session_id": "2", 
        "actions": [{
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

async def repo_get_session():
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

async def repo_delete_session():
    class DeletedSession:
        def __init__(self):
            self.deleted_count = 1
    return DeletedSession()


def create_mock_session_data():
    return {
        "session_id": "60d5ec49f1a4a21f6c8b4561",
        "course": "Курс молодого бойца",
        "email": "iiivanov@edu.ru",
        "student": "Иванов Иван",
        "student_id": 1,
        "actions": [{
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
            }
        ]
    }


async def repo_add_session():
    return {
        "_id": "60d5ec49f1a4a21f6c8b4567", 
        "session_id": "60d5ec49f1a4a21f6c8b4561",
        "course": "Курс молодого бойца",
        "email": "iiivanov@edu.ru",
        "student": "Иванов Иван",
        "student_id": 1,
        "actions": [{
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


def create_mock_page_data():
    return {
        "page": "http://e.moevm.info",
        "title": "kakoy-to title",
        "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
        "page_html": '<html></html>',
        "window": {
            "width": 1200,
            "height": 800
        }
    }


async def repo_create_page():
    return {
        "_id": "60d5ec49f1a4a21f6c8b4567",
        "page": "http://e.moevm.info",
        "title": "kakoy-to title",
        "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
        "page_html": '<html></html>',
        "window": {
            "width": 1200,
            "height": 800
        }
    }


async def repo_get_all_records():
    return [{
            "_id": "60d5ec49f1a4a21f6c8b4567",
            "page": "http://e.moevm.info",
            "title": "kakoy-to title",
            "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
            "page_html": '<html></html>',
            "window": {
                "width": 1200,
                "height": 800
            }
        }, 
        {
            "_id": "60d5ec49f1a4a21f6c8b4568",
            "page": "http://e.moevm.info",
            "title": "kakoy-to title",
            "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
            "page_html": '<html></html>',
            "window": {
                "width": 1200,
                "height": 800
            }
        }]