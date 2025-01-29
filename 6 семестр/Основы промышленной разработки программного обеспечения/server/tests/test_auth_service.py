from unittest.mock import Mock
import pytest


from src.core.modules.service.authorization import AuthService
from src.core.modules.database.errors import RepoNotFoundError, RepoEmptyDataError
from src.core.modules.service.errors import UserNotFoundError, UserEmptyDataError

@pytest.mark.asyncio
async def test_sign_in_success():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_user_by_email.return_value = get_user()
    expected_email = 'email'
    expected_password = 'password'
    service = AuthService(mock_repo)

    # Act
    result = await service.sign_in(expected_email, expected_password)

    # Assert
    assert result["email"] == expected_email
    assert result["password"] == expected_password


@pytest.mark.asyncio
async def test_sign_in_fail_not_found():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_user_by_email.side_effect = RepoNotFoundError()
    expected_email = 'email'
    expected_password = 'password'
    service = AuthService(mock_repo)
    try:
        # Act
        result = await service.sign_in(expected_email, expected_password)
    except Exception as e:
        # Assert
        assert isinstance(e, UserNotFoundError)

@pytest.mark.asyncio
async def test_sign_in_fail_empty_data():
    # Arrange
    mock_repo = Mock()
    mock_repo.get_user_by_email.side_effect = RepoEmptyDataError()
    expected_email = 'email'
    expected_password = 'password'
    service = AuthService(mock_repo)
    try:
        # Act
        result = await service.sign_in(expected_email, expected_password)
    except Exception as e:
        # Assert
        assert isinstance(e, UserEmptyDataError)

async def get_user():
    return {"password": "password", "email": "email"}