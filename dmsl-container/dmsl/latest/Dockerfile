FROM ubuntu:latest

# Add user
RUN groupadd DmslRunner
RUN useradd -m -d /home/DmslRunner -g DmslRunner -s /bin/bash DmslRunner

# Install dmsl
RUN apt update
RUN apt upgrade -y
RUN apt install cmake git -y
RUN apt install make -y
RUN apt install -y build-essential
RUN cd /home/DmslRunner && git clone https://github.com/740291272/DmslRunner.git && cd DmslRunner/compiler && cmake . && make && make install
ADD https://github.com/740291272/DmslRunner/releases/download/Build/dmslrunner /home/DmslRunner/dmslrunner
RUN chmod a+x /home/DmslRunner/dmslrunner

USER DmslRunner
WORKDIR /home/DmslRunner/
EXPOSE 8008
