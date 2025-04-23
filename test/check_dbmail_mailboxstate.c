/*
 *   Copyright (c) 2004-2013 NFG Net Facilities Group BV support@nfg.nl
 *   Copyright (c) 2014-2019 Paul J Stevens, The Netherlands, support@nfg.nl
 *   Copyright (c) 2020-2024 Alan Hicks, Persistent Objects Ltd support@p-o.co.uk
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either
 *   version 2 of the License, or (at your option) any later
 *   version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 *   
 *
 *
 *  
 *
 *   Basic unit-test framework for dbmail (www.dbmail.org)
 *
 *   See http://check.sf.net for details and docs.
 *
 *
 *   Run 'make check' to see some action.
 *
 */ 

#include <check.h>
#include "check_dbmail.h"

extern char configFile[PATH_MAX];

#define TESTBOX "testbox.TMP"
uint64_t testboxid = 0;
uint64_t testuserid = 0;

/*
 *
 * the test fixtures
 *
 */
static uint64_t get_mailbox_id(const char *username, const char *boxname)
{
	int result;
	uint64_t id;
	result = auth_user_exists(username, &testuserid);
	ck_assert_uint_eq (result, 1);
	ck_assert_uint_gt (testuserid, 0);
	result = db_find_create_mailbox(boxname, BOX_COMMANDLINE, testuserid, &id);
	ck_assert_uint_eq (result, DM_SUCCESS);
	ck_assert_uint_gt (id, 0);
	return id;
}

static void insert_message(void)
{
	uint64_t newmsgidnr = 0;
	DbmailMessage *message;
	message = dbmail_message_new(NULL);
	message = dbmail_message_init_with_string(message,multipart_message);
	dbmail_message_store(message);
	db_copymsg(message->msg_idnr, testboxid, testuserid, &newmsgidnr);
}

void setup(void)
{
	config_get_file();
	config_read(configFile);
	configure_debug(NULL,255,0);
	GetDBParams();
	db_connect();
	auth_connect();
	do_add("mailboxstate1","secretmailboxstate","md5-hash",1024,0,NULL,NULL);
	do_add("mailboxstate2","secretmailboxstate","md5-hash",0,0,NULL,NULL);
	testboxid = get_mailbox_id("mailboxstate1", TESTBOX);
}

void teardown(void)
{
	db_delete_mailbox(testboxid, 0, 0);
	db_disconnect();
}

START_TEST(test_createdestroy)
{
	uint64_t id = get_mailbox_id("testuser1", "INBOX");
	MailboxState_T M = MailboxState_new(NULL, id);
	MailboxState_free(&M);
}
END_TEST

START_TEST(test_metadata)
{
	// Test user who goes over quota
	int result = 0;
	testboxid = get_mailbox_id("mailboxstate1", "metadata1");
	MailboxState_T M = MailboxState_new(NULL, testboxid);
	result = MailboxState_count(M);
	ck_assert_uint_eq (result, DM_SUCCESS);
	ck_assert_uint_eq (MailboxState_getUnseen(M), 0);
	ck_assert_uint_eq (MailboxState_getRecent(M), 0);
	ck_assert_uint_eq (MailboxState_getExists(M), 0);

	insert_message();

	result = MailboxState_count(M);
	ck_assert_uint_eq (result, DM_SUCCESS);
	ck_assert_uint_eq (MailboxState_getUnseen(M), 0);
	ck_assert_uint_eq (MailboxState_getRecent(M), 0);
	ck_assert_uint_eq (MailboxState_getExists(M), 0);
	MailboxState_free(&M);

	// Test user below quota
	testboxid = get_mailbox_id("mailboxstate2", "metadata2");
	ck_assert_uint_gt (testboxid, 0);

	M = MailboxState_new(NULL, testboxid);
	result = MailboxState_count(M);
	ck_assert_uint_eq (result, DM_SUCCESS);
	ck_assert_uint_eq (MailboxState_getUnseen(M), 0);
	ck_assert_uint_eq (MailboxState_getRecent(M), 0);
	ck_assert_uint_eq (MailboxState_getExists(M), 0);

	insert_message();

	result = MailboxState_count(M);
	ck_assert_uint_eq (result, DM_SUCCESS);
	ck_assert_uint_eq (MailboxState_getUnseen(M), 1);
	ck_assert_uint_eq (MailboxState_getRecent(M), 1);
	ck_assert_uint_eq (MailboxState_getExists(M), 1);
	MailboxState_free(&M);
}
END_TEST

static void mailboxstate_destroy(MailboxState_T M)
{
	MailboxState_free(&M);
}


START_TEST(test_mbxinfo)
{
	MailboxState_T N, M;
	GTree *mbxinfo = g_tree_new_full((GCompareDataFunc)ucmpdata,NULL,(GDestroyNotify)g_free,(GDestroyNotify)mailboxstate_destroy);
	uint64_t *k1, *k2;
	uint64_t id = get_mailbox_id("testuser1", "INBOX");

	k1 = g_new0(uint64_t,1);
	k2 = g_new0(uint64_t,1);

	*k1 = id;
	*k2 = id;

	N = MailboxState_new(NULL, id);
	g_tree_replace(mbxinfo, k1, N);

	M = MailboxState_new(NULL, id);
	g_tree_replace(mbxinfo, k2, M);

	g_tree_destroy(mbxinfo);
}
END_TEST


Suite *dbmail_common_suite(void)
{
	Suite *s = suite_create("Dbmail MailboxState");
	TCase *tc_state = tcase_create("MailboxState");
	
	suite_add_tcase(s, tc_state);
	
	tcase_add_checked_fixture(tc_state, setup, teardown);
	tcase_add_test(tc_state, test_createdestroy);
	tcase_add_test(tc_state, test_metadata);
	tcase_add_test(tc_state, test_mbxinfo);

	return s;
}

int main(void)
{
	int nf;
	Suite *s = dbmail_common_suite();
	SRunner *sr = srunner_create(s);
	g_mime_init();
	srunner_run_all(sr, CK_NORMAL);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);
	g_mime_shutdown();
	return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
	

