#!/bin/sh

set -eu

name="${1:-world}"
echo "Hello ${name}"

# Gebruik een stabiel format (UTC, ISO-achtig) voor CI logs
now="$(date -u +"%Y-%m-%dT%H:%M:%SZ")"

# Schrijf output op de GitHub Actions-manier
if [ -z "${GITHUB_OUTPUT:-}" ]; then
  echo "GITHUB_OUTPUT is not set; are you running inside GitHub Actions?" >&2
  exit 1
fi

printf 'time=%s\n' "$now" >> "$GITHUB_OUTPUT"
