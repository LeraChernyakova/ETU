from typing import List

from fastapi import APIRouter, HTTPException, Body
from fastapi.encoders import jsonable_encoder
from starlette import status
from starlette.responses import JSONResponse

from src.core.modules.service.errors import UserNotFoundError, UserAlreadyExistsError, UserEmptyDataError
from src.depends import get_user_service
from src.models.user import User, UpdateUser, CreateUser

router = APIRouter()

service = get_user_service()


@router.get(
    "/",
    status_code=status.HTTP_200_OK,
    response_description="List all users",
    response_model=List[User],
    response_model_by_alias=False
)
async def get_all_users():
    try:
        return await service.get_all_users()
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@router.get(
    "/{user_id}",
    status_code=status.HTTP_200_OK,
    response_description="Retrieve a user",
    response_model=User,
    response_model_by_alias=False,
)
async def get_user(user_id: str):
    try:
        return await service.get_user(user_id)
    except Exception as e:
        if isinstance(e, UserNotFoundError):
            raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User not found: {str(e)}")
        else:
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@router.post(
    "/",
    status_code=status.HTTP_201_CREATED,
    response_description="Add new user",
    response_model=User,
    response_model_by_alias=False,
)
async def create_user(user_data: CreateUser = Body()):
    try:
        user = jsonable_encoder(user_data)
        return await service.create_user(user)
    except Exception as e:
        if isinstance(e, UserAlreadyExistsError):
            raise HTTPException(status_code=status.HTTP_409_CONFLICT, detail=f"User already exists: {str(e)}")
        else:
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@router.put(
    "/{user_id}",
    status_code=status.HTTP_200_OK,
    response_description="Update user",
    response_model_by_alias=False,
    response_model=User
)
async def update_user(user_id: str, user_data: UpdateUser = Body()):
    try:
        return await service.update_user(user_id, user_data)
    except Exception as e:
        if isinstance(e, UserNotFoundError):
            raise HTTPException(status_code=status.HTTP_404_NOT_FOUND,
                                detail=f"Updating user {user_id} failed: {str(e)}")
        elif isinstance(e, UserEmptyDataError):
            raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST,
                                detail=f"Updating user {user_id} failed: {str(e)}")
        else:
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@router.delete(
    "/{user_id}",
    status_code=status.HTTP_204_NO_CONTENT,
    response_description="Delete a user",
)
async def delete_user(user_id: str):
    try:
        res = await service.delete_user(user_id)
        if res.deleted_count == 1:
            return JSONResponse(status_code=status.HTTP_204_NO_CONTENT, content={"message": "Deleted successfully"})
    except Exception as e:
        if isinstance(e, UserNotFoundError):
            raise HTTPException(status_code=status.HTTP_404_NOT_FOUND,
                                detail=f"Deleting user {user_id} failed: {str(e)}")
        else:
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))
