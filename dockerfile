# syntax=docker/dockerfile:1.7

ARG UBUNTU_VERSION=22.04
FROM --platform=$BUILDPLATFORM ubuntu:${UBUNTU_VERSION}

ENV DEBIAN_FRONTEND=noninteractive

# Optioneel: timezone instelbaar bij build
ARG TZ=Etc/UTC
ENV TZ=${TZ}

# Gebruik bash met pipefail voor betrouwbaardere RUN-steps
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# Core tooling voor development/debugging
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      tzdata \
      vim \
      build-essential \
      git \
      cmake \
      net-tools \
      gdb \
      clang \
 && ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime \
 && echo ${TZ} > /etc/timezone \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# Maak een niet-root gebruiker (handig voor devcontainers/CI)
ARG USER=dev
ARG UID=1000
ARG GID=1000
RUN groupadd -g ${GID} ${USER} \
 && useradd -m -u ${UID}
