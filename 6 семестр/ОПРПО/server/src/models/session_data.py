import uuid
from pydantic import BaseModel, EmailStr, HttpUrl, Field
from datetime import datetime
from typing import List


class Payload(BaseModel):
    timestamp: datetime = Field(default_factory=lambda: datetime.now().isoformat())
    element_type: str = Field(...)
    element_name: str = Field(...)
    action_type: str = Field(...)
    event_type: str = Field(...)
    element_html: str = Field(..., description="The HTML content of the element")

    class Config:
        populate_by_field_name = True
        arbitrary_types_allowed = True
        json_schema_extra = {
            "examples": [
                {
                    "timestamp": datetime.now().isoformat(),
                    "element_type": "button",
                    "element_name": "отправить",
                    "action_type": "conversation",
                    "event_type": "mousedown",
                    "element_html": "<input/>"
                },
                {
                    "timestamp": datetime.now().isoformat(),
                    "element_type": "page",
                    "element_name": "сохранить",
                    "action_type": "hidden",
                    "event_type": "visibilitychange",
                    "element_html": "<input/>"
                },
                {
                    "timestamp": datetime.now().isoformat(),
                    "element_type": "page",
                    "element_name": "сохранить",
                    "action_type": "visible",
                    "event_type": "visibilitychange",
                    "element_html": "<input/>"
                }
            ]
        }


class SessionData(BaseModel):
    id: str = Field(default_factory=lambda: str(uuid.uuid4()), alias="_id")
    student_id: int = Field(...)
    session_id: str = Field(...)
    student: str = Field(...)
    email: EmailStr = Field(...)
    course: str = Field(...)
    actions: List[Payload] = Field(default_factory=list)

    class Config:
        populate_by_field_name = True
        arbitrary_types_allowed = True
        json_schema_extra = {
            "examples": [
                {
                    "id": str(uuid.uuid4()),
                    "student_id": 1,
                    "session_id": str(uuid.uuid4()),
                    "student": "Иванов Иван",
                    "email": "iiivanov@edu.ru",
                    "course": "Курс молодого бойца",
                    "actions": [{
                        "timestamp": datetime.now().isoformat(),
                        "element_type": "button",
                        "element_name": "сохранить",
                        "action_type": "conversation",
                        "event_type": "mousedown",
                        "element_html": "<input/>"
                    }]
                },
                {
                    "id": str(uuid.uuid4()),
                    "student_id": 1,
                    "session_id": str(uuid.uuid4()),
                    "student": "Иванов Иван",
                    "email": "iiivanov@edu.ru",
                    "course": "Курс молодого бойца",
                    "actions": [{
                        "timestamp": datetime.now().isoformat(),
                        "element_type": "button",
                        "element_name": "сохранить",
                        "action_type": "hidden",
                        "event_type": "visibilitychange",
                        "element_html": "<input/>"
                    }]
                },
                {
                    "id": str(uuid.uuid4()),
                    "student": "Иванов Иван",
                    "student_id": 1,
                    "session_id": str(uuid.uuid4()),
                    "email": "iiivanov@edu.ru",
                    "course": "Курс молодого бойца",
                    "actions": [{
                        "timestamp": datetime.now().isoformat(),
                        "element_type": "page",
                        "element_name": "сохранить",
                        "action_type": "visible",
                        "event_type": "visibilitychange",
                        "element_html": "<input/>"
                    }]
                }
            ]
        }


class CreateSessionData(BaseModel):
    student_id: int = Field(...)
    session_id: str = Field(...)
    student: str = Field(...)
    email: EmailStr = Field(...)
    course: str = Field(...)
    actions: List[Payload] = Field(default_factory=list)

    class Config:
        populate_by_field_name = True
        arbitrary_types_allowed = True
        json_schema_extra = {
            "examples": [
                {
                    "student_id": 1,
                    "session_id": str(uuid.uuid4()),
                    "student": "Иванов Иван",
                    "email": "iiivanov@edu.ru",
                    "course": "Курс молодого бойца",
                    "actions": [{
                        "timestamp": datetime.now().isoformat(),
                        "element_type": "button",
                        "element_name": "сохранить",
                        "action_type": "conversation",
                        "event_type": "mousedown",
                        "element_html": "<input/>"
                    }]
                },
                {
                    "student_id": 1,
                    "session_id": str(uuid.uuid4()),
                    "student": "Иванов Иван",
                    "email": "iiivanov@edu.ru",
                    "course": "Курс молодого бойца",
                    "actions": [{
                        "timestamp": datetime.now().isoformat(),
                        "element_type": "page",
                        "element_name": "сохранить",
                        "action_type": "hidden",
                        "event_type": "visibilitychange",
                        "element_html": "<input/>"
                    }]
                },
                {
                    "student_id": 1,
                    "session_id": str(uuid.uuid4()),
                    "student": "Иванов Иван",
                    "email": "iiivanov@edu.ru",
                    "course": "Курс молодого бойца",
                    "actions": [{
                        "timestamp": datetime.now().isoformat(),
                        "element_type": "page",
                        "element_name": "сохранить",
                        "action_type": "visible",
                        "event_type": "visibilitychange",
                        "element_html": "<input/>"
                    }]
                }
            ]
        }


class Window(BaseModel):
    width: int = Field(...)
    height: int = Field(...)


class PageData(BaseModel):
    id: str = Field(default_factory=lambda: str(uuid.uuid4()), alias="_id")
    page: HttpUrl = Field(...)
    browser: str = Field(...)
    title: str = Field(...)
    page_html: str = Field(...)
    window: Window = Field(...)

    class Config:
        populate_by_field_name = True
        arbitrary_types_allowed = True
        json_schema_extra = {
            "example": {
                "id": str(uuid.uuid4()),
                "page": "http://e.moevm.info",
                "title": "kakoy-to title",
                "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
                "page_html": '<html></html>',
                "window": {
                    "width": 1200,
                    "height": 800
                }
            }
        }


class CreatePageData(BaseModel):
    page: HttpUrl = Field(...)
    browser: str = Field(...)
    title: str = Field(...)
    page_html: str = Field(...)
    window: Window = Field(...)

    class Config:
        populate_by_field_name = True
        arbitrary_types_allowed = True
        json_schema_extra = {
            "example": {
                "page": "http://e.moevm.info",
                "title": "kakoy-to title",
                "browser": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit",
                "page_html": '<html></html>',
                "window": {
                    "width": 1200,
                    "height": 800
                }
            }
        }
