from datetime import datetime
from typing import Optional

from fastapi.params import Query
from pydantic import BaseModel, Field


class SessionFilter(BaseModel):
    begin_timestamp: Optional[datetime] = Field(Query(default=None, description="start date"))
    end_timestamp: Optional[datetime] = Field(Query(default=None, description="stop date"))
    student_id: Optional[int] = Field(Query(default=None, description="student moodle id"))
    student_name: Optional[str] = Field(Query(default=None, description="student FIO"))
    student_email: Optional[str] = Field(Query(default=None, description="student email"))
    course_title: Optional[str] = Field(Query(default=None, description="name of the course"))
    action_type: Optional[str] = Field(Query(default=None, description="action type"))
    event_type: Optional[str] = Field(Query(default=None, description="event type"))
    element_type: Optional[str] = Field(Query(default=None, description="element type"))
    element_name: Optional[str] = Field(Query(default=None, description="element name"))

    def query(self) -> dict:
        filter_dict = {}
        action_filter = {}
        if self.begin_timestamp or self.end_timestamp:
            timestamp_filter = {}
            if self.begin_timestamp:
                timestamp_filter['$gte'] = self.begin_timestamp
            if self.end_timestamp:
                timestamp_filter['$lte'] = self.end_timestamp
            if timestamp_filter:
                action_filter['timestamp'] = timestamp_filter

        if self.action_type:
            action_filter['action_type'] = {'$regex': self.action_type, '$options': 'i'}
        if self.event_type:
            action_filter['event_type'] = {'$regex': self.event_type, '$options': 'i'}
        if self.element_type:
            action_filter['element_type'] = {'$regex': self.element_type, '$options': 'i'}
        if self.element_name:
            action_filter['element_name'] = {'$regex': self.element_name, '$options': 'i'}

        if action_filter:
            filter_dict['actions'] = {'$elemMatch': action_filter}

        if self.student_id:
            filter_dict['student_id'] = self.student_id
        if self.student_name:
            filter_dict['student'] = {'$regex': self.student_name, '$options': 'i'}
        if self.student_email:
            filter_dict['email'] = {'$regex': self.student_email, '$options': 'i'}
        if self.course_title:
            filter_dict['course'] = {'$regex': self.course_title, '$options': 'i'}

        return filter_dict
