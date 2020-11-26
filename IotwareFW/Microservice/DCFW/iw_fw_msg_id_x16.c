/*
Copyright (C) <2020> <ETRI>

This License and Service Agreement (LSA) applies to all works and their derivative works based on source form version and object form version of IoTware Project. Currently, the LSA for IoTware Project has two policies, 'Open Source License' and 'Commercial License'. Therefore, all works including the source code and executable code of IoTware Project and derivative works based thereon are subject to either 'Open Source License' or 'Commercial License' depending on the user's needs and purpose. Details related to the selection of the applicable license are specified in this LSA. If you use any or all of IoTware Project in any form, you are deemed to have consented to this LSA. If you breach any of the terms and conditions set forth in this LSA, you are solely responsible for any losses or damages incurred by Electronics and Communications Research Institute (ETRI), and ETRI assume no responsibility for you or any third party.
If you use the source form version or object form version of IoTware Project in whole or in part to develop a code or a derivative work, and you want to commercialize the result in some form, you will be covered under a commercial license. And if you are subject to a commercial license, the contract for the use of IoTware Project is subject to TECHNOLOGY LICENSE AGREEMENT of ETRI. You acknowledge that ETRI has all legal rights, title and interest, including intellectual property rights in the IoTware Project (regardless of whether such intellectual property rights are registered or where such rights exist) and agree with no objection thereto. Except as provided in a subsidiary agreement, nothing in this LSA grants you the right to use IoTware Project or the name, service mark, logo, domain name and other unique identification marks of ETRI.
If you use the source form version or object form version of IoTware Project in whole or in part to develop a code or a derivative work, and you do not commercialize the result in any form, you will be covered under an open source license. IoTware Project is in accordance with Free Software Foundation (FSF)'s open source policy, and is allowed to use it in the appropriate scope and manner, and you must comply with the applicable open source license policy applied to IoTware Project. IoTware Project is, in principle, subject to GNU Lesser General Public License version 2.1 (LGPLv2.1). If you have acquired all or a part of the IoTware Project in any way and it is subject to a license other than the open source license described above, please contact the following address for the technical support and other inquiries before use, and check the usage information.
*/

#include "iw_fw_msg_id_x16.h"

#pragma pack(push, 1)

static struct CMAttributeReadMsg cmATTRIBUTE_READ = {
	{
		.ack = CM_ACK_REQ_MSG,
		.message_id = CM_MSG_ID_ATTRIBUTE_READ,
		.dup = 0,
		.qos = CM_QOS_ACK_NEED
	},
	.reserved = 0,
	.length = 0
};

static struct CMAttributeReadAckMsg cmATTRIBUTE_READ_ACK = {
	{
		.ack = CM_ACK_MSG_ID,
		.message_id = CM_MSG_ID_ATTRIBUTE_READ_ACK,
		.dup = 0,
		.qos = CM_QOS_ACK_NONE,
		.reserved = 0,
		.return_code = 0
	},
	.reserved = 0,
	.length = 0
};

#pragma pack(pop)

static size_t sizeof_attribute_read()
{
	return sizeof(struct CMAttributeReadMsg) - sizeof(struct CMAttributeReadPayload *);
}

static size_t sizeof_payload()
{
	return sizeof(struct CMAttributeReadPayload) - sizeof(struct CMAttributePayload *);
}

uint8_t *cm_msg_x16_serialize(const struct CMAttributeReadMsg *msg, size_t *size)
{
	*size = sizeof_attribute_read() + sizeof_payload() + cm_attributes_serialize_size(msg->payload->attr_count + 1);
	uint8_t *buf = calloc(1, *size);
	size_t sz = sizeof_attribute_read();
	if(buf!=NULL)
		memcpy(buf, msg, sz);
	if (msg->payload) {
		memcpy(buf+sz, msg->payload, sizeof_payload());
		sz += sizeof_payload();
		cm_attributes_serialize(msg->payload->attributes, msg->payload->attr_count + 1, buf+sz);
	}
	return buf;
}

static struct CMAttributeReadPayload *payload_parse(const uint8_t *msg, const size_t size)
{
	struct CMAttributeReadPayload *payload = NULL;
	size_t sz = sizeof_payload();
	if (size >= sz) {
		payload = calloc(1, sizeof(struct CMAttributeReadPayload));
		const uint8_t *pt = msg;
		if(payload!=NULL){
			memcpy(payload, pt, sz);
			pt += sz;
			payload->attributes = cm_attributes_parse(pt, size - sz, payload->attr_count);
		}
	}
	return payload;
}

struct CMAttributeReadMsg cm_msg_x16_parse(const uint8_t *msg, const size_t size)
{
	struct CMAttributeReadMsg buf;
	size_t sz = sizeof_attribute_read();
	if (size >= sz) {
		const uint8_t *pt = msg;
		memcpy(&buf, pt, sz);
		pt += sz;
		buf.payload = payload_parse(pt, size - sz);
	}
	return buf;
}

struct CMAttributeReadMsg cm_msg_x16()
{
	return cmATTRIBUTE_READ;
}

static size_t sizeof_attribute_read_ack()
{
	return sizeof(struct CMAttributeReadAckMsg) - sizeof(struct CMAttributeReadAckPayload *);
}

static size_t sizeof_ack_payload()
{
	return sizeof(struct CMAttributeReadAckPayload) - sizeof(struct CMAttributeValuePayload *);
}

uint8_t *cm_msg_x16_ack_serialize(const struct CMAttributeReadAckMsg *msg, size_t *size)
{
	*size = sizeof_attribute_read_ack() + sizeof_ack_payload() + cm_attribute_values_serialize_size(msg->payload->attribute_values, msg->payload->attr_count + 1);
	uint8_t *buf = calloc(1, *size);
	size_t sz = sizeof_attribute_read_ack();
	if(buf!=NULL){
		memcpy(buf, msg, sz);
		if (msg->payload) {
			memcpy(buf+sz, msg->payload, sizeof_ack_payload());
			sz += sizeof_ack_payload();
			cm_attribute_values_serialize(msg->payload->attribute_values, msg->payload->attr_count + 1, buf+sz);
		}
	}
	return buf;
}

static struct CMAttributeReadAckPayload *ack_payload_parse(const uint8_t *msg, const size_t size)
{
	struct CMAttributeReadAckPayload *payload = NULL;
	size_t sz = sizeof_ack_payload();
	if (size >= sz) {
		payload = calloc(1, sizeof(struct CMAttributeReadAckPayload));
		const uint8_t *pt = msg;
		if(payload!=NULL){
			memcpy(payload, pt, sz);
			pt += sz;
			payload->attribute_values = cm_attribute_values_parse(pt, size - sz, payload->attr_count);
		}
	}
	return payload;
}

struct CMAttributeReadAckMsg cm_msg_x16_ack_parse(const uint8_t *msg, const size_t size)
{
	struct CMAttributeReadAckMsg buf;
	size_t sz = sizeof_attribute_read_ack();
	if (size >= sz) {
		const uint8_t *pt = msg;
		memcpy(&buf, pt, sz);
		pt += sz;
		buf.payload = ack_payload_parse(pt, size - sz);
	}
	return buf;
}

struct CMAttributeReadAckMsg cm_msg_x16_ack()
{
	return cmATTRIBUTE_READ_ACK;
}
