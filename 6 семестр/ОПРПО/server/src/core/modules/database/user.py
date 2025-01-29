from bson.objectid import ObjectId

from src.core.modules.database.errors import RepoNotFoundError, RepoAlreadyExistsError, RepoEmptyDataError


class MongoUserRepo:
    def __init__(self, client):
        self.client = client

    async def get_all_users(self) -> list:
        users = []
        for user in await self.client.users.find().to_list(length=None):
            user['_id'] = str(user['_id'])
            users.append(user)
        return users

    async def get_user(self, user_id: str) -> dict:
        user = await self.client.users.find_one({"_id": ObjectId(user_id)})
        if user:
            user['_id'] = str(user['_id'])
            return user
        raise RepoNotFoundError(f"user with id {user_id} not found")

    async def get_user_by_email(self, email: str) -> dict:
        if len(email) == 0:
            raise RepoEmptyDataError(f"invalid email length")
        user = await self.client.users.find_one({"email": email})
        if user:
            user['_id'] = str(user['_id'])
            return user
        raise RepoNotFoundError(f"user with email {email} not found")

    async def add_user(self, user_data: dict) -> dict:
        if await self.client.users.find_one({"email": user_data["email"]}) is not None:
            raise RepoAlreadyExistsError(f"user with email {user_data['email']} already exists")
        user = await self.client.users.insert_one(user_data)
        new_user = await self.client.users.find_one({"_id": user.inserted_id})
        new_user['_id'] = str(new_user['_id'])
        return new_user

    async def update_user(self, user_id: str, data: dict) -> dict:
        if len(data) < 1:
            raise RepoEmptyDataError("empty request body")
        user = await self.client.users.find_one({"_id": ObjectId(user_id)})
        if not user:
            raise RepoNotFoundError(f"user with id {user_id} not found")
        await self.client.users.update_one(
            {"_id": ObjectId(user_id)}, {"$set": data}
        )
        updated_user = await self.client.users.find_one({"_id": ObjectId(user_id)})
        updated_user["_id"] = str(updated_user["_id"])
        return updated_user

    async def delete_user(self, user_id: str):
        user = await self.client.users.find_one({"_id": ObjectId(user_id)})
        if user:
            return await self.client.users.delete_one({"_id": ObjectId(user_id)})
        raise RepoNotFoundError(f"user with id {user_id} not found")
