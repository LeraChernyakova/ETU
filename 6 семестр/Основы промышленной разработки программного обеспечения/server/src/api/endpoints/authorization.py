from fastapi import APIRouter, HTTPException, Body
from fastapi.encoders import jsonable_encoder
from starlette import status
from starlette.responses import JSONResponse

from src.core.modules.service.errors import UserNotFoundError, UserEmptyDataError
from src.depends import get_auth_service
from src.models.user import User, SignInData

router = APIRouter()

service = get_auth_service()


@router.post(
    "/sign-in",
    status_code=status.HTTP_200_OK,
    response_description="User authorization",
    response_model=User,
    response_model_by_alias=False,
)
async def signin(user_raw_data: SignInData = Body()):
    try:
        user_data = jsonable_encoder(user_raw_data)
        user = await service.sign_in(user_data["email"], user_data["password"])
        if not user:
            return JSONResponse(status_code=status.HTTP_401_UNAUTHORIZED, content={"message": "Invalid credentials"})
        return user
    except Exception as e:
        if isinstance(e, UserNotFoundError):
            raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail=f"User not found: {str(e)}")
        elif isinstance(e, UserEmptyDataError):
            raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=f"Invalid user data: {str(e)}")
        else:
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))
