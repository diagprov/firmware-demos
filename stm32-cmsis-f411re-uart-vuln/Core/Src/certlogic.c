
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "internal/macros.h"
#include "internal/utils.h"
#include "asinine/dsl.h"
#include "asinine/x509.h"
#include "certlogic.h"

#define WEAK __attribute__((weak))

WEAK void uart_tx_message(const char* message) {
}

static const signed char decoding_table[] = {62,-1,-1,-1,63,52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-2,-1,-1,-1,0,1,2,3,4,
5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
41,42,43,44,45,46,47,48,49,50,51};

bool base64_decode(char* decoded_data,
                   const char *input_data,
                   size_t input_length,
                   size_t *output_length) {

    if (input_length % 4 != 0) return false;

    *output_length = input_length / 4 * 3;
    if (input_data[input_length - 1] == '=') (*output_length)--;
    if (input_data[input_length - 2] == '=') (*output_length)--;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]-43];
        uint32_t sextet_b = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]-43];
        uint32_t sextet_c = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]-43];
        uint32_t sextet_d = input_data[i] == '=' ? 0 & i++ : decoding_table[input_data[i++]-43];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return true;
}

void dump_name(const x509_name_t *name) {
	char buf[10] = {0};

	for (size_t i = 0; i < name->num; i++) {
		const x509_rdn_t *rdn = &name->rdns[i];

		snprintf(buf, sizeof(buf), "%s:", x509_rdn_type_string(rdn->type));
        uart_tx_message(buf); memset(buf, 0, sizeof buf);

		asinine_err_t err = asn1_string(&rdn->value, buf, sizeof(buf));
        /** DELIBERATE BUG: FORMAT STRING VULN. **/
		if (err.errno != ASININE_OK) {
			sprintf(buf, asinine_strerror(err));
		} else {
			sprintf(buf, buf);
		}
        uart_tx_message(buf); memset(buf, 0, sizeof buf);
        uart_tx_message("\r\n");
	}
}

void dump_certificate(const x509_cert_t *cert) {
	char buf[256];

    uart_tx_message("---\r\n");
	sprintf(buf, "Version: %d, Algo: %d\r\n", cert->version, cert->signature.algorithm);
    uart_tx_message(buf); memset(buf, 0, sizeof buf);

    //assert(asn1_time_to_string(buf, sizeof(buf), &cert->valid_from) < sizeof(buf));
	sprintf(buf, "Valid from: %s", buf);
    uart_tx_message(buf); memset(buf, 0, sizeof buf);

	//assert(asn1_time_to_string(buf, sizeof(buf), &cert->valid_to) < sizeof(buf));
	sprintf(buf, ", to: %s\r\n", buf);
    uart_tx_message(buf); memset(buf, 0, sizeof buf);

	sprintf(buf, "Issuer:");
	dump_name(&cert->issuer);
    uart_tx_message(buf); memset(buf, 0, sizeof buf);

	sprintf(buf, "Subject:");
	dump_name(&cert->subject);
    uart_tx_message(buf); memset(buf, 0, sizeof buf);

	sprintf(buf, "Public key: %d\r\n", cert->pubkey.algorithm);
    uart_tx_message(buf); memset(buf, 0, sizeof buf);
}

void echo_certificates(const uint8_t *contents, size_t length) {
	x509_cert_t cert;

	asn1_parser_t parser;
	asn1_init(&parser, contents, length);

	asinine_err_t res = ERROR(ASININE_OK, NULL);
	while (!asn1_end(&parser)) {
		asinine_err_t err = x509_parse_cert(&parser, &cert);
		if (err.errno != ASININE_OK) {
			fprintf(stderr, "Invalid certificate: %s\n", asinine_strerror(err));
			if (res.errno == ASININE_OK) {
				res = err;
			}

			RETURN_ON_ERROR(asn1_abort(&parser));
		} else {
			dump_certificate(&cert);
		}
	}
}
