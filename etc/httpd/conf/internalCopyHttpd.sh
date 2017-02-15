rm -rf /apps/serverApps/apache/conf/httpd.conf.OLD;
mv /apps/serverApps/apache/conf/httpd.conf /apps/serverApps/apache/conf/httpd.conf.OLD;
cp /home/apache/HAE/etc/httpd/conf/httpd.conf.internal /apps/serverApps/apache/conf/httpd.conf;
/apps/serverApps/apache/bin/apachectl stop;
/apps/serverApps/apache/bin/apachectl start;