import os
import motor.motor_asyncio as aio_motor
from dotenv import load_dotenv

from src.core.modules.database.statistics import MongoStatisticRepo, MongoPageRepo
from src.core.modules.database.user import MongoUserRepo
from src.core.modules.service.authorization import AuthService
from src.core.modules.service.statistics import StatisticsService
from src.core.modules.service.user import UserService


load_dotenv()

user = os.getenv('MONGODB_INITDB_ROOT_USERNAME')
password = os.getenv('MONGODB_INITDB_ROOT_PASSWORD')

client = aio_motor.AsyncIOMotorClient(f'mongodb://{user}:{password}@mongodb:27017/?authMechanism=DEFAULT')
user_service = UserService(MongoUserRepo(client["moodle-statistics"]))
statistics_service = StatisticsService(MongoStatisticRepo(client["moodle-statistics"]), MongoPageRepo(client["moodle-statistics"]))
auth_service = AuthService(MongoUserRepo(client["moodle-statistics"]))


def get_user_service() -> UserService:
    return user_service


def get_statistics_service() -> StatisticsService:
    return statistics_service


def get_auth_service() -> AuthService:
    return auth_service
