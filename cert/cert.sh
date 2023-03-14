#!/usr/bin/bash

# https://ivanzz1001.github.io/records/post/linuxops/2018/03/21/linux-openssl-usage


# openssl genrsa -out rsa_private.key 2048 
	# --numbits 2048 # 私钥长度(bits)
	# -des, -des3, -idea, -seed, -aes128, -aes192, -aes256 encrypt
# openssl rsa -in rsa_private.key -pubout -out rsa_public.key

openssl genrsa -aes256 -passout pass:123456 -out rsa_aes_private.key 2048
openssl rsa -in rsa_aes_private.key -passin pass:123456 -pubout -out rsa_public2.key
openssl rsa -in rsa_aes_private.key -passin pass:123456 -out rsa_private.key
# openssl rsa -in rsa_private.key -aes256 -passout pass:123456 -out rsa_aes_private2.key 
openssl rsa -in rsa_private.key -outform der -out rsa_private.der
openssl rsa -in rsa_private.key -noout -text -check
openssl pkcs8 -topk8 -in rsa_private.key -passout pass:123456 -out pkcs8_private.key # -nocrypt
openssl req -newkey rsa:2048 -nodes -keyout cert_private.key -x509 -days 365 -out cert.crt -subj "/C=CN/ST=GuangDong/L=ShenZhen/O=test_company/OU=IT/CN=test_name/emailAddress=test_mail@xx.com"
# openssl req -new -key rsa_private.key -x509 -days 365 -out cert.crt -subj "/C=CN/ST=GuangDong/L=ShenZhen/O=test_company/OU=IT/CN=test_name/emailAddress=test_name@xx.com"
openssl req -new -key rsa_aes_private.key -passin pass:123456 -out server.csr -subj "/C=CN/ST=GuangDong/L=ShenZhen/O=test_company/OU=IT/CN=127.0.0.1/emailAddress=name@xx.com"
openssl x509 -req -days 365 -in server.csr -CA cert.crt -CAkey cert_private.key -passin pass:123456 -CAcreateserial -out server.crt
openssl verify -CAfile cert.crt server.crt
openssl x509 -in server.crt -noout -text

openssl x509 -in cert.crt -inform PEM -outform DER -out cert.der
openssl pkcs12 -export -in cert.crt -inkey cert_private.key -password pass:123456 -out cert.p12
openssl pkcs12 -export -in server.crt -inkey rsa_aes_private.key -passin pass:123456 -chain -CAfile cert.crt -password pass:123456 -out all.p12 
openssl pkcs12 -in all.p12 -password pass:123456 -passout pass:123456 -out key.pem
openssl pkcs12 -in all.p12 -password pass:123456 -nokeys -cacerts -out ca.pem
openssl pkcs12 -in all.p12 -password pass:123456 -nokeys -clcerts -out cert.pem

# rm -rf *.der *.pem *p12 *.crt *.key *.csr
