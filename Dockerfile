FROM gcc:16.1

COPY . /home/lines
WORKDIR /home/lines
RUN apt-get update
RUN apt-get install cmake -y
RUN apt-get install python3.13-dev -y
RUN apt-get install python3.13-venv -y

