#! /bin/bash

set -e

COMMON_NAME=${DOMAIN_NAME:-"localhost"}

mkdir -p /etc/nginx/ssl

if [ ! -f /etc/nginx/ssl/nginx.key ] || [ ! -f /etc/nginx/ssl/nginx.crt ]; then
	echo " => Generating self-signed SSL certificate..."
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout /etc/nginx/ssl/nginx.key \
	-out /etc/nginx/ssl/nginx.crt \
	-subj "/C=MY/ST=KL/L=KL/O=42KL/OU=Inception/CN=${COMMON_NAME}"
	chmod 600 /etc/nginx/ssl/nginx.key
	echo " => Self-signed SSL certificate generated."
else
	echo " => SSL certificate already exists. Skipping generation."
fi

envsubst '$DOMAIN_NAME' < /etc/nginx/sites-available/inception.conf.tmp > /etc/nginx/sites-available/inception.conf

ln -sf /etc/nginx/sites-available/inception.conf /etc/nginx/sites-enabled/inception.conf

echo " => Starting Nginx in daemon off..."
exec nginx -g "daemon off;"
echo " => Nginx started."
