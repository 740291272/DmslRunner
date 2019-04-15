FROM ubuntu:latest
MAINTAINER gloomyghost

# Add user
RUN groupadd DmslRunner
RUN useradd -m -d /home/DmslRunner -g DmslRunner -s /bin/bash DmslRunner

# Install dmsl
RUN apt update
RUN apt upgrade -y
RUN apt install cmake git -y
RUN apt install make -y
RUN apt install -y build-essential
RUN cd /home/DmslRunner && git clone https://github.com/740291272/DmslRunner.git && cd DmslRunner/compiler && cmake . && make
RUN chmod +x /home/DmslRunner/DmslRunner/dmsl-runner

USER DmslRunner
WORKDIR /home/DmslRunner/
CMD ["/home/DmslRunner/DmslRunner/dmsl-runner"]
ENTRYPOINT "/home/DmslRunner/DmslRunner/dmsl-runner"
EXPOSE 8008
