FROM ubuntu:latest

# Add user
RUN groupadd DmslRunner
RUN useradd -m -d /home/DmslRunner -g DmslRunner -s /bin/bash DmslRunner

# Install dmsl
RUN apt update
RUN apt upgrade -y
RUN apt install cmake git -y
RUN apt install make -y
RUN apt install build-essential python3 -y
RUN cd /home/DmslRunner && git clone https://github.com/740291272/DmslRunner.git && cd DmslRunner/compiler && cmake . && make && make install
RUN echo 0.11
RUN cd /home/DmslRunner/DmslRunner && git pull
RUN cp /home/DmslRunner/DmslRunner/dmsl-runner/main.py /home/DmslRunner/main.py
RUN chmod a+x /home/DmslRunner/main.py

USER DmslRunner
WORKDIR /home/DmslRunner/
EXPOSE 8008
