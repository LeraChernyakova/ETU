import pymongo
from fastapi import APIRouter, HTTPException
from starlette import status

from src.depends import client

router = APIRouter()


@router.get(
    "/",
    status_code=status.HTTP_200_OK,
    response_description="Healthcheck ping",
    response_model_by_alias=False
)
async def healthcheck():
    try:
        with pymongo.timeout(5):
            return await client["moodle-statistics"].command("ping")
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail={"message": "Database instance is unhealthy", "error": str(e)})