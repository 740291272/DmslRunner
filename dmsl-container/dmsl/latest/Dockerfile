FROM ubuntu:latest

# Add user
RUN groupadd DmslRunner
RUN useradd -m -d /home/DmslRunner -g DmslRunner -s /bin/bash DmslRunner

# Install dmsl
RUN apt update
RUN apt upgrade -y
RUN apt install cmake git -y
RUN git clone https://github.com/740291272/DmslRunner.git
RUN cd ./DmslRunner/compiler
RUN cmake .
RUN make
RUN chmod +x /home/DmslRunner/dmsl-runner

USER DmslRunner
WORKDIR /home/DmslRunner/
CMD ["/home/DmslRunner/dmsl-runner"]
ENTRYPOINT "/home/DmslRunner/dmsl-runner"
