FROM debian:bullseye-slim

RUN apt-get update && \
	apt-get install -y --no-install-recommends nginx openssl gettext-base curl && \
	apt-get clean && rm -rf /var/lib/apt/lists/*

COPY ./conf/inception.conf /etc/nginx/sites-available/inception.conf.tmp
# RUN ln -s /etc/nginx/sites-available/inception.conf /etc/nginx/sites-enabled/
# RUN rm /etc/nginx/sites-enabled/default

COPY ./tools/init.sh /init.sh
RUN chmod +x /init.sh

ENTRYPOINT ["/init.sh"]
