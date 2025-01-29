import os
from typing import List

import bson.json_util as json
from fastapi import APIRouter, HTTPException, Body, Depends
from fastapi.encoders import jsonable_encoder
from starlette import status

from starlette.responses import JSONResponse, FileResponse

from src.core.modules.service.errors import SessionNotFoundError
from src.depends import get_statistics_service
from src.models.filter import SessionFilter
from src.models.session_data import SessionData, CreateSessionData
from src.models.session_data import PageData, CreatePageData

router = APIRouter()
download_router = APIRouter()
service = get_statistics_service()


@router.get(
    "/",
    status_code=status.HTTP_200_OK,
    response_description="Get statistics",
    response_model=List[SessionData],
    response_model_by_alias=False
)
async def get_all_sessions(params: SessionFilter = Depends()):
    try:
        return await service.get_all_sessions(params)
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@router.get(
    "/{session_id}",
    status_code=status.HTTP_200_OK,
    response_description="Get session statistic",
    response_model=SessionData,
    response_model_by_alias=False
)
async def get_session_by_id(session_id: str):
    try:
        return await service.get_session(session_id)
    except Exception as e:
        if isinstance(e, SessionNotFoundError):
            raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Session not found")
        else:
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@router.post(
    "/",
    status_code=status.HTTP_201_CREATED,
    response_description="Add new session",
    response_model=SessionData,
    response_model_by_alias=False
)
async def create_session(session: CreateSessionData = Body()):
    try:
        session = jsonable_encoder(session)
        return await service.create_session(session)
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=str(e))


@router.delete(
    "/{session_id}",
    status_code=status.HTTP_204_NO_CONTENT,
    response_description="Delete a session statistic",
)
async def delete_session(session_id: str):
    try:
        res = await service.delete_session(session_id)
        if res.deleted_count == 1:
            return JSONResponse(status_code=status.HTTP_204_NO_CONTENT, content={"message": "Deleted successfully"})
    except Exception as e:
        if isinstance(e, SessionNotFoundError):
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail=f"Deleting session {session_id} failed: {str(e)}"
            )
        else:
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@download_router.get(
    "/statistics",
    response_description="Download statistics"
)
async def download_data(params: SessionFilter = Depends()):
    try:
        data = await service.get_all_sessions(params)
        with open(os.path.join(os.path.curdir, 'data.json'), mode='w+b') as f:
            f.truncate(0)
            f.write(json.dumps(data, ensure_ascii=False).encode('utf-8'))
        return FileResponse(
            os.path.join(os.path.curdir, 'data.json'),
            filename="data.json",
            media_type='application/octet-stream'
        )
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))


@router.post(
    "/page",
    status_code=status.HTTP_201_CREATED,
    response_model=str,
    response_model_by_alias=False
)
async def create_page(page: CreatePageData = Body()):
    try:
        page = jsonable_encoder(page)
        created_page = await service.create_page(page)
        return created_page['_id']
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail=str(e))


@download_router.get(
    "/sessions",
    response_description="Download sessions"
)
async def download_sessions():
    try:
        data = await service.get_pages()
        with open(os.path.join(os.path.curdir, 'sessions.json'), mode='w+b') as f:
            f.truncate(0)
            f.write(json.dumps(data, ensure_ascii=False).encode('utf-8'))
        return FileResponse(
            os.path.join(os.path.curdir, 'sessions.json'),
            filename="sessions.json",
            media_type='application/octet-stream'
        )
    except Exception as e:
        raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR, detail=str(e))