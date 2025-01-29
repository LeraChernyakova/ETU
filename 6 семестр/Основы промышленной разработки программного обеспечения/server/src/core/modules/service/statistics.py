import logging
from datetime import datetime

from bson import ObjectId
from src.core.modules.database.errors import RepoNotFoundError
from src.core.modules.service.errors import SessionNotFoundError

from src.models.filter import SessionFilter


class StatisticsService:
    def __init__(self, repo, pages):
        self.repo = repo
        self.pages = pages

    async def get_all_sessions(self, filters: SessionFilter):
        try:
            return await self.repo.get_all_sessions(filters)
        except Exception as e:
            logging.error(f"error getting all sessions: {str(e)}")
            raise

    async def get_session(self, session_id):
        try:
            return await self.repo.get_session(session_id)
        except Exception as e:
            if isinstance(e, RepoNotFoundError):
                logging.error(f"error getting session {session_id}: {str(e)}")
                raise SessionNotFoundError(f"error getting session {session_id}: {str(e)}") from e
            else:
                raise

    async def delete_session(self, session_id):
        try:
            return await self.repo.delete_session(session_id)
        except Exception as e:
            if isinstance(e, RepoNotFoundError):
                logging.error(f"error deleting session {session_id}: {str(e)}")
                raise SessionNotFoundError(f"error deleting session {session_id}: {str(e)}") from e
            else:
                raise

    async def create_session(self, session_data):
        try:
            session_data['session_id'] = ObjectId(session_data['session_id'])
            for action in session_data["actions"]:
                action["timestamp"] = datetime.fromisoformat(action["timestamp"])
            return await self.repo.add_session(session_data)
        except Exception as e:
            logging.error(f'error creating session data {session_data}: {str(e)}')
            raise Exception(f'error creating session data {session_data}: {str(e)}') from e

    async def create_page(self, page_data):
        try:
            return await self.pages.create_record(page_data)
        except Exception as e:
            logging.error(f'error creating page {page_data}: {str(e)}')
            raise Exception(f'error creating page {page_data}: {str(e)}') from e

    async def get_pages(self):
        try:
            return await self.pages.get_all_records()
        except Exception as e:
            logging.error(f"error getting all pages: {str(e)}")
            raise
