FROM python:3.12.2-alpine3.19
ENV PATH=$PATH:root/.local/bin
COPY ./requirements.txt .
RUN pip install --user -r requirements.txt
COPY . ./
ENV TZ="Europe/Moscow"
CMD ["python", "-u", "main.py"]