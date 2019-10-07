FROM php:apache
RUN apt update
RUN apt install libpng-dev -y
RUN docker-php-ext-install gd
RUN a2enmod rewrite && service apache2 restart
COPY webapp /var/www/html
RUN chmod -R 777 /var/www/html
