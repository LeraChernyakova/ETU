from copy import deepcopy

from bson.objectid import ObjectId
from src.core.modules.database.errors import RepoNotFoundError
from src.models.filter import SessionFilter


class MongoStatisticRepo:
    def __init__(self, client):
        self.client = client

    async def get_all_sessions(self, filters: SessionFilter) -> list:
        stats = []
        query = filters.query()
        for session in await self.client.statistics.find(query).to_list(length=None):
            session["_id"] = str(session["_id"])
            session["session_id"] = str(session["session_id"])
            session['actions'] = filter_actions(filters, session['actions'])
            stats.append(session)
        return stats

    async def get_session(self, record_id: str) -> dict:
        stat = await self.client.statistics.find_one({"_id": ObjectId(record_id)})
        if stat:
            stat["_id"] = str(stat["_id"])
            stat["session_id"] = str(stat["session_id"])
            return stat
        raise RepoNotFoundError(f'record {record_id} not found')

    async def add_session(self, session_data: dict) -> dict:
        stat = await self.client.statistics.insert_one(session_data)
        new_stat = await self.client.statistics.find_one({"_id": stat.inserted_id})
        new_stat["_id"] = str(new_stat["_id"])
        new_stat['session_id'] = str(new_stat['session_id'])
        return new_stat

    async def delete_session(self, record_id: str):
        stat = await self.client.statistics.find_one({"_id": ObjectId(record_id)})
        if stat:
            return await self.client.statistics.delete_one({"_id": ObjectId(record_id)})
        raise RepoNotFoundError(f'record {record_id} not found')


def filter_actions(query: SessionFilter, payload: list) -> list:
    if not query:
        return payload
    data = deepcopy(payload)
    if query.action_type:
        data = filter(lambda item: query.action_type in str(item['action_type']), data)
    if query.event_type:
        data = filter(lambda item: query.event_type in str(item['event_type']), data)
    if query.element_type:
        data = filter(lambda item: query.element_type in str(item['element_type']), data)
    if query.element_name:
        data = filter(lambda item: query.element_name in str(item['element_name']), data)
    if query.begin_timestamp:
        data = filter(lambda item: query.begin_timestamp <= item['timestamp'], data)
    if query.end_timestamp:
        data = filter(lambda item: query.end_timestamp >= item['timestamp'], data)
    return list(data)


class MongoPageRepo:
    def __init__(self, client):
        self.client = client

    async def create_record(self, page_data: dict) -> dict:
        page = await self.client.sessions.insert_one(page_data)
        new_page = await self.client.sessions.find_one({"_id": page.inserted_id})
        new_page["_id"] = str(new_page["_id"])
        return new_page

    async def get_all_records(self) -> list:
        pages = []
        for page in await self.client.sessions.find().to_list(length=None):
            page["_id"] = str(page["_id"])
            pages.append(page)
        return pages