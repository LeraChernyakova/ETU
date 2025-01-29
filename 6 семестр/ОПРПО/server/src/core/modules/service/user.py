import logging
from src.core.modules.database.errors import RepoNotFoundError, RepoAlreadyExistsError, RepoEmptyDataError
from src.core.modules.service.errors import UserNotFoundError, UserAlreadyExistsError, UserEmptyDataError
from src.models.user import Role, UpdateUser


class UserService:
    def __init__(self, repo):
        self.repo = repo

    async def get_all_users(self):
        try:
            return await self.repo.get_all_users()
        except Exception as e:
            logging.error(f'error getting users: {str(e)}')
            raise

    async def get_user(self, user_id):
        try:
            return await self.repo.get_user(user_id)
        except Exception as e:
            if isinstance(e, RepoNotFoundError):
                logging.error(f'error getting user {user_id}: {str(e)}')
                raise UserNotFoundError(f'error getting user {user_id}: {str(e)}') from e
            else:
                raise

    async def create_user(self, user_data):
        try:
            user_data["position"] = Role.regular
            return await self.repo.add_user(user_data)
        except Exception as e:
            if isinstance(e, RepoAlreadyExistsError):
                logging.error(f'error creating user {user_data}: {str(e)}')
                raise UserAlreadyExistsError(f'error creating user {user_data}: {str(e)}') from e
            else:
                raise

    async def update_user(self, user_id, user_data: UpdateUser):
        try:
            return await self.repo.update_user(user_id, user_data.dict())
        except Exception as e:
            if isinstance(e, RepoEmptyDataError):
                logging.error(f'error updating user {user_id}: {str(e)}')
                raise UserEmptyDataError(f'error updating user {user_id}: {str(e)}') from e
            elif isinstance(e, RepoNotFoundError):
                logging.error(f'error updating user {user_id}: {str(e)}')
                raise UserNotFoundError(f'error updating user {user_id}: {str(e)}') from e
            else:
                raise

    async def delete_user(self, user_id):
        try:
            return await self.repo.delete_user(user_id)
        except Exception as e:
            if isinstance(e, RepoNotFoundError):
                logging.error(f'error deleting user {user_id}: {str(e)}')
                raise UserNotFoundError(f'error deleting user {user_id}: {str(e)}') from e
            else:
                raise

