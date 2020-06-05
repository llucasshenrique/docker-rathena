FROM php:apache
#RUN apt update
#RUN apt install libpng-dev -y
#RUN docker-php-ext-install gd
RUN docker-php-ext-install pdo_mysql
RUN a2enmod rewrite && service apache2 restart
COPY fluxcp-source /var/www/html
RUN chmod -R 777 /var/www/html
RUN chown -R 33:33 /var/www/html/
