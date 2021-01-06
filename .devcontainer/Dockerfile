ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN export DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get -y install --no-install-recommends clang-tidy clang-format clangd 