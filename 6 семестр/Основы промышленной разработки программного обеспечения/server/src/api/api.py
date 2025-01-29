from fastapi import APIRouter
from src.api.endpoints import statistics, user, authorization, healthcheck

api_router = APIRouter()
api_router.include_router(statistics.router, prefix="/statistics", tags=["statistics"])
api_router.include_router(user.router, prefix="/user", tags=["user"])
api_router.include_router(authorization.router, prefix="/auth", tags=["authorization"])
api_router.include_router(healthcheck.router, prefix="/healthcheck", tags=["healthcheck"])
api_router.include_router(statistics.download_router, prefix="/download", tags=["download"])