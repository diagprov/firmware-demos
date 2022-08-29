
#pragma once

bool base64_decode(char* decoded_data,
                   const char *input_data,
                   size_t input_length,
                   size_t *output_length);
void dump_certificate(const x509_cert_t *cert);
void echo_certificates(const uint8_t *contents, size_t length);
