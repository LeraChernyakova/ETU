from unittest.mock import Mock
import pytest

from src.core.modules.database.statistics import MongoPageRepo


@pytest.mark.asyncio
async def test_create_record():
    # Arrange
    mock_client = Mock()
    mock_client.sessions.insert_one.return_value = insert_one()
    mock_client.sessions.find_one.return_value = find_one()
    expected_id = '60d5ec49f1a4a21f6c8b4567'
    page_data = create_page_data()
    repository = MongoPageRepo(mock_client)

    # Act
    result = await repository.create_record(page_data)

    # Assert
    assert result["_id"] == expected_id
    assert result["window"]["width"] and result["window"]["height"]


@pytest.mark.asyncio
async def test_get_all_records():
    # Arrange
    mock_client = Mock()
    mock_client.sessions.find.return_value.to_list.return_value = \
          find_to_list()
    expected_id_1 = '60d5ec49f1a4a21f6c8b4567'
    expected_id_2 = '60d5ec49f1a4a21f6c8b4568'
    repository = MongoPageRepo(mock_client)
    
    # Act
    result = await repository.get_all_records()

    # Assert
    assert len(result) == 2
    assert int(result[0]["_id"], 16)
    assert int(result[1]["_id"], 16)
    assert result[0]["_id"] == expected_id_1
    assert result[1]["_id"] == expected_id_2

async def insert_one():
    class CreatedPage:
        def __init__(self):
            self.inserted_id = "60d5ec49f1a4a21f6c8b4567"
            self.id = "60d5ec49f1a4a21f6c8b4567"

    return CreatedPage()

async def find_one():
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

def create_page_data():
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

async def find_to_list():
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