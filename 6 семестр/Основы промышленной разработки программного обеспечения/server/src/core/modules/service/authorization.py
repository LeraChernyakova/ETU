import logging

from src.core.modules.database.errors import RepoNotFoundError, RepoEmptyDataError
from src.core.modules.service.errors import UserNotFoundError, UserEmptyDataError


class AuthService:
    def __init__(self, repo):
        self.repo = repo

    async def sign_in(self, email, password):
        try:
            user = await self.repo.get_user_by_email(email)
            if user["password"] == password:
                return user
        except Exception as e:
            if isinstance(e, RepoNotFoundError):
                logging.error(f'error authorizing user: {str(e)}')
                raise UserNotFoundError(f'error authorizing user: {str(e)}') from e
            elif isinstance(e, RepoEmptyDataError):
                logging.error(f'error authorizing user: {str(e)}')
                raise UserEmptyDataError(f'error authorizing user: {str(e)}') from e
            else:
                raise
