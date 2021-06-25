#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0
#
# A collection of tests for tools/testing/kunit/kunit.py
#
# Copyright (C) 2019, Google LLC.
# Author: Brendan Higgins <brendanhiggins@google.com>

import unittest
from unittest import mock

import tempfile, shutil # Handling test_tmpdir

import json
<<<<<<< HEAD
import signal
=======
<<<<<<< HEAD
import signal
=======
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
import os

import kunit_config
import kunit_parser
import kunit_kernel
import kunit_json
import kunit

test_tmpdir = ''
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
abs_test_data_dir = ''

def setUpModule():
	global test_tmpdir, abs_test_data_dir
	test_tmpdir = tempfile.mkdtemp()
	abs_test_data_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), 'test_data'))
<<<<<<< HEAD
=======
=======

def setUpModule():
	global test_tmpdir
	test_tmpdir = tempfile.mkdtemp()
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

def tearDownModule():
	shutil.rmtree(test_tmpdir)

<<<<<<< HEAD
def test_data_path(path):
	return os.path.join(abs_test_data_dir, path)
=======
<<<<<<< HEAD
def test_data_path(path):
	return os.path.join(abs_test_data_dir, path)
=======
def get_absolute_path(path):
	return os.path.join(os.path.dirname(__file__), path)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

class KconfigTest(unittest.TestCase):

	def test_is_subset_of(self):
		kconfig0 = kunit_config.Kconfig()
		self.assertTrue(kconfig0.is_subset_of(kconfig0))

		kconfig1 = kunit_config.Kconfig()
		kconfig1.add_entry(kunit_config.KconfigEntry('TEST', 'y'))
		self.assertTrue(kconfig1.is_subset_of(kconfig1))
		self.assertTrue(kconfig0.is_subset_of(kconfig1))
		self.assertFalse(kconfig1.is_subset_of(kconfig0))

	def test_read_from_file(self):
		kconfig = kunit_config.Kconfig()
<<<<<<< HEAD
		kconfig_path = test_data_path('test_read_from_file.kconfig')
=======
<<<<<<< HEAD
		kconfig_path = test_data_path('test_read_from_file.kconfig')
=======
		kconfig_path = get_absolute_path(
			'test_data/test_read_from_file.kconfig')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

		kconfig.read_from_file(kconfig_path)

		expected_kconfig = kunit_config.Kconfig()
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('UML', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('MMU', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('TEST', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('EXAMPLE_TEST', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('MK8', 'n'))

		self.assertEqual(kconfig.entries(), expected_kconfig.entries())

	def test_write_to_file(self):
		kconfig_path = os.path.join(test_tmpdir, '.config')

		expected_kconfig = kunit_config.Kconfig()
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('UML', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('MMU', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('TEST', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('EXAMPLE_TEST', 'y'))
		expected_kconfig.add_entry(
			kunit_config.KconfigEntry('MK8', 'n'))

		expected_kconfig.write_to_file(kconfig_path)

		actual_kconfig = kunit_config.Kconfig()
		actual_kconfig.read_from_file(kconfig_path)

		self.assertEqual(actual_kconfig.entries(),
				 expected_kconfig.entries())

class KUnitParserTest(unittest.TestCase):

	def assertContains(self, needle, haystack):
		for line in haystack:
			if needle in line:
				return
		raise AssertionError('"' +
			str(needle) + '" not found in "' + str(haystack) + '"!')

	def test_output_isolated_correctly(self):
<<<<<<< HEAD
		log_path = test_data_path('test_output_isolated_correctly.log')
		with open(log_path) as file:
			result = kunit_parser.isolate_kunit_output(file.readlines())
=======
<<<<<<< HEAD
		log_path = test_data_path('test_output_isolated_correctly.log')
		with open(log_path) as file:
			result = kunit_parser.isolate_kunit_output(file.readlines())
=======
		log_path = get_absolute_path(
			'test_data/test_output_isolated_correctly.log')
		file = open(log_path)
		result = kunit_parser.isolate_kunit_output(file.readlines())
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertContains('TAP version 14', result)
		self.assertContains('	# Subtest: example', result)
		self.assertContains('	1..2', result)
		self.assertContains('	ok 1 - example_simple_test', result)
		self.assertContains('	ok 2 - example_mock_test', result)
		self.assertContains('ok 1 - example', result)
<<<<<<< HEAD

	def test_output_with_prefix_isolated_correctly(self):
		log_path = test_data_path('test_pound_sign.log')
=======
<<<<<<< HEAD

	def test_output_with_prefix_isolated_correctly(self):
		log_path = test_data_path('test_pound_sign.log')
=======
		file.close()

	def test_output_with_prefix_isolated_correctly(self):
		log_path = get_absolute_path(
			'test_data/test_pound_sign.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(log_path) as file:
			result = kunit_parser.isolate_kunit_output(file.readlines())
		self.assertContains('TAP version 14', result)
		self.assertContains('	# Subtest: kunit-resource-test', result)
		self.assertContains('	1..5', result)
		self.assertContains('	ok 1 - kunit_resource_test_init_resources', result)
		self.assertContains('	ok 2 - kunit_resource_test_alloc_resource', result)
		self.assertContains('	ok 3 - kunit_resource_test_destroy_resource', result)
		self.assertContains(' foo bar 	#', result)
		self.assertContains('	ok 4 - kunit_resource_test_cleanup_resources', result)
		self.assertContains('	ok 5 - kunit_resource_test_proper_free_ordering', result)
		self.assertContains('ok 1 - kunit-resource-test', result)
		self.assertContains(' foo bar 	# non-kunit output', result)
		self.assertContains('	# Subtest: kunit-try-catch-test', result)
		self.assertContains('	1..2', result)
		self.assertContains('	ok 1 - kunit_test_try_catch_successful_try_no_catch',
				    result)
		self.assertContains('	ok 2 - kunit_test_try_catch_unsuccessful_try_does_catch',
				    result)
		self.assertContains('ok 2 - kunit-try-catch-test', result)
		self.assertContains('	# Subtest: string-stream-test', result)
		self.assertContains('	1..3', result)
		self.assertContains('	ok 1 - string_stream_test_empty_on_creation', result)
		self.assertContains('	ok 2 - string_stream_test_not_empty_after_add', result)
		self.assertContains('	ok 3 - string_stream_test_get_string', result)
		self.assertContains('ok 3 - string-stream-test', result)

	def test_parse_successful_test_log(self):
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		all_passed_log = test_data_path('test_is_test_passed-all_passed.log')
		with open(all_passed_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
		self.assertEqual(
			kunit_parser.TestStatus.SUCCESS,
			result.status)

	def test_parse_failed_test_log(self):
		failed_log = test_data_path('test_is_test_passed-failure.log')
		with open(failed_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
		self.assertEqual(
			kunit_parser.TestStatus.FAILURE,
			result.status)

	def test_no_tests(self):
		empty_log = test_data_path('test_is_test_passed-no_tests_run.log')
		with open(empty_log) as file:
			result = kunit_parser.parse_run_tests(
				kunit_parser.isolate_kunit_output(file.readlines()))
<<<<<<< HEAD
=======
=======
		all_passed_log = get_absolute_path(
			'test_data/test_is_test_passed-all_passed.log')
		file = open(all_passed_log)
		result = kunit_parser.parse_run_tests(file.readlines())
		self.assertEqual(
			kunit_parser.TestStatus.SUCCESS,
			result.status)
		file.close()

	def test_parse_failed_test_log(self):
		failed_log = get_absolute_path(
			'test_data/test_is_test_passed-failure.log')
		file = open(failed_log)
		result = kunit_parser.parse_run_tests(file.readlines())
		self.assertEqual(
			kunit_parser.TestStatus.FAILURE,
			result.status)
		file.close()

	def test_no_tests(self):
		empty_log = get_absolute_path(
			'test_data/test_is_test_passed-no_tests_run.log')
		file = open(empty_log)
		result = kunit_parser.parse_run_tests(
			kunit_parser.isolate_kunit_output(file.readlines()))
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(0, len(result.suites))
		self.assertEqual(
			kunit_parser.TestStatus.NO_TESTS,
			result.status)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	def test_no_kunit_output(self):
		crash_log = test_data_path('test_insufficient_memory.log')
		print_mock = mock.patch('builtins.print').start()
		with open(crash_log) as file:
			result = kunit_parser.parse_run_tests(
				kunit_parser.isolate_kunit_output(file.readlines()))
<<<<<<< HEAD
=======
=======
		file.close()

	def test_no_kunit_output(self):
		crash_log = get_absolute_path(
			'test_data/test_insufficient_memory.log')
		file = open(crash_log)
		print_mock = mock.patch('builtins.print').start()
		result = kunit_parser.parse_run_tests(
			kunit_parser.isolate_kunit_output(file.readlines()))
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		print_mock.assert_any_call(StrContains('no tests run!'))
		print_mock.stop()
		file.close()

	def test_crashed_test(self):
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		crashed_log = test_data_path('test_is_test_passed-crash.log')
		with open(crashed_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
		self.assertEqual(
			kunit_parser.TestStatus.TEST_CRASHED,
			result.status)

	def test_ignores_prefix_printk_time(self):
		prefix_log = test_data_path('test_config_printk_time.log')
<<<<<<< HEAD
=======
=======
		crashed_log = get_absolute_path(
			'test_data/test_is_test_passed-crash.log')
		file = open(crashed_log)
		result = kunit_parser.parse_run_tests(file.readlines())
		self.assertEqual(
			kunit_parser.TestStatus.TEST_CRASHED,
			result.status)
		file.close()

	def test_ignores_prefix_printk_time(self):
		prefix_log = get_absolute_path(
			'test_data/test_config_printk_time.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(prefix_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
			self.assertEqual(
				kunit_parser.TestStatus.SUCCESS,
				result.status)
			self.assertEqual('kunit-resource-test', result.suites[0].name)

	def test_ignores_multiple_prefixes(self):
<<<<<<< HEAD
		prefix_log = test_data_path('test_multiple_prefixes.log')
=======
<<<<<<< HEAD
		prefix_log = test_data_path('test_multiple_prefixes.log')
=======
		prefix_log = get_absolute_path(
			'test_data/test_multiple_prefixes.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(prefix_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
			self.assertEqual(
				kunit_parser.TestStatus.SUCCESS,
				result.status)
			self.assertEqual('kunit-resource-test', result.suites[0].name)

	def test_prefix_mixed_kernel_output(self):
<<<<<<< HEAD
		mixed_prefix_log = test_data_path('test_interrupted_tap_output.log')
=======
<<<<<<< HEAD
		mixed_prefix_log = test_data_path('test_interrupted_tap_output.log')
=======
		mixed_prefix_log = get_absolute_path(
			'test_data/test_interrupted_tap_output.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(mixed_prefix_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
			self.assertEqual(
				kunit_parser.TestStatus.SUCCESS,
				result.status)
			self.assertEqual('kunit-resource-test', result.suites[0].name)

	def test_prefix_poundsign(self):
<<<<<<< HEAD
		pound_log = test_data_path('test_pound_sign.log')
=======
<<<<<<< HEAD
		pound_log = test_data_path('test_pound_sign.log')
=======
		pound_log = get_absolute_path('test_data/test_pound_sign.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(pound_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
			self.assertEqual(
				kunit_parser.TestStatus.SUCCESS,
				result.status)
			self.assertEqual('kunit-resource-test', result.suites[0].name)

	def test_kernel_panic_end(self):
<<<<<<< HEAD
		panic_log = test_data_path('test_kernel_panic_interrupt.log')
=======
<<<<<<< HEAD
		panic_log = test_data_path('test_kernel_panic_interrupt.log')
=======
		panic_log = get_absolute_path('test_data/test_kernel_panic_interrupt.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(panic_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
			self.assertEqual(
				kunit_parser.TestStatus.TEST_CRASHED,
				result.status)
			self.assertEqual('kunit-resource-test', result.suites[0].name)

	def test_pound_no_prefix(self):
<<<<<<< HEAD
		pound_log = test_data_path('test_pound_no_prefix.log')
=======
<<<<<<< HEAD
		pound_log = test_data_path('test_pound_no_prefix.log')
=======
		pound_log = get_absolute_path('test_data/test_pound_no_prefix.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(pound_log) as file:
			result = kunit_parser.parse_run_tests(file.readlines())
			self.assertEqual(
				kunit_parser.TestStatus.SUCCESS,
				result.status)
			self.assertEqual('kunit-resource-test', result.suites[0].name)

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
class LinuxSourceTreeTest(unittest.TestCase):

	def setUp(self):
		mock.patch.object(signal, 'signal').start()
		self.addCleanup(mock.patch.stopall)

	def test_invalid_kunitconfig(self):
		with self.assertRaisesRegex(kunit_kernel.ConfigError, 'nonexistent.* does not exist'):
			kunit_kernel.LinuxSourceTree('', kunitconfig_path='/nonexistent_file')

	def test_valid_kunitconfig(self):
		with tempfile.NamedTemporaryFile('wt') as kunitconfig:
			tree = kunit_kernel.LinuxSourceTree('', kunitconfig_path=kunitconfig.name)

	# TODO: add more test cases.


class KUnitJsonTest(unittest.TestCase):

	def _json_for(self, log_file):
		with open(test_data_path(log_file)) as file:
<<<<<<< HEAD
=======
=======
class KUnitJsonTest(unittest.TestCase):

	def _json_for(self, log_file):
		with(open(get_absolute_path(log_file))) as file:
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
			test_result = kunit_parser.parse_run_tests(file)
			json_obj = kunit_json.get_json_result(
				test_result=test_result,
				def_config='kunit_defconfig',
				build_dir=None,
				json_path='stdout')
		return json.loads(json_obj)

	def test_failed_test_json(self):
<<<<<<< HEAD
		result = self._json_for('test_is_test_passed-failure.log')
=======
<<<<<<< HEAD
		result = self._json_for('test_is_test_passed-failure.log')
=======
		result = self._json_for(
			'test_data/test_is_test_passed-failure.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(
			{'name': 'example_simple_test', 'status': 'FAIL'},
			result["sub_groups"][1]["test_cases"][0])

	def test_crashed_test_json(self):
<<<<<<< HEAD
		result = self._json_for('test_is_test_passed-crash.log')
=======
<<<<<<< HEAD
		result = self._json_for('test_is_test_passed-crash.log')
=======
		result = self._json_for(
			'test_data/test_is_test_passed-crash.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(
			{'name': 'example_simple_test', 'status': 'ERROR'},
			result["sub_groups"][1]["test_cases"][0])

	def test_no_tests_json(self):
<<<<<<< HEAD
		result = self._json_for('test_is_test_passed-no_tests_run.log')
=======
<<<<<<< HEAD
		result = self._json_for('test_is_test_passed-no_tests_run.log')
=======
		result = self._json_for(
			'test_data/test_is_test_passed-no_tests_run.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(0, len(result['sub_groups']))

class StrContains(str):
	def __eq__(self, other):
		return self in other

class KUnitMainTest(unittest.TestCase):
	def setUp(self):
<<<<<<< HEAD
		path = test_data_path('test_is_test_passed-all_passed.log')
=======
<<<<<<< HEAD
		path = test_data_path('test_is_test_passed-all_passed.log')
=======
		path = get_absolute_path('test_data/test_is_test_passed-all_passed.log')
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		with open(path) as file:
			all_passed_log = file.readlines()

		self.print_mock = mock.patch('builtins.print').start()
		self.addCleanup(mock.patch.stopall)

		self.linux_source_mock = mock.Mock()
		self.linux_source_mock.build_reconfig = mock.Mock(return_value=True)
		self.linux_source_mock.build_um_kernel = mock.Mock(return_value=True)
		self.linux_source_mock.run_kernel = mock.Mock(return_value=all_passed_log)

	def test_config_passes_args_pass(self):
		kunit.main(['config', '--build_dir=.kunit'], self.linux_source_mock)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 0)

	def test_build_passes_args_pass(self):
		kunit.main(['build'], self.linux_source_mock)
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 0)
		self.linux_source_mock.build_um_kernel.assert_called_once_with(False, 8, '.kunit', None)
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 0)

	def test_exec_passes_args_pass(self):
		kunit.main(['exec'], self.linux_source_mock)
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 0)
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 1)
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', filter_glob='', timeout=300)
<<<<<<< HEAD
=======
=======
		assert self.linux_source_mock.build_reconfig.call_count == 1
		assert self.linux_source_mock.run_kernel.call_count == 0

	def test_build_passes_args_pass(self):
		kunit.main(['build'], self.linux_source_mock)
		assert self.linux_source_mock.build_reconfig.call_count == 0
		self.linux_source_mock.build_um_kernel.assert_called_once_with(False, 8, '.kunit', None)
		assert self.linux_source_mock.run_kernel.call_count == 0

	def test_exec_passes_args_pass(self):
		kunit.main(['exec'], self.linux_source_mock)
		assert self.linux_source_mock.build_reconfig.call_count == 0
		assert self.linux_source_mock.run_kernel.call_count == 1
		self.linux_source_mock.run_kernel.assert_called_once_with(build_dir='.kunit', timeout=300)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.print_mock.assert_any_call(StrContains('Testing complete.'))

	def test_run_passes_args_pass(self):
		kunit.main(['run'], self.linux_source_mock)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 1)
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', filter_glob='', timeout=300)
<<<<<<< HEAD
=======
=======
		assert self.linux_source_mock.build_reconfig.call_count == 1
		assert self.linux_source_mock.run_kernel.call_count == 1
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', timeout=300)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.print_mock.assert_any_call(StrContains('Testing complete.'))

	def test_exec_passes_args_fail(self):
		self.linux_source_mock.run_kernel = mock.Mock(return_value=[])
		with self.assertRaises(SystemExit) as e:
			kunit.main(['exec'], self.linux_source_mock)
<<<<<<< HEAD
		self.assertEqual(e.exception.code, 1)
=======
<<<<<<< HEAD
		self.assertEqual(e.exception.code, 1)
=======
		assert type(e.exception) == SystemExit
		assert e.exception.code == 1
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	def test_run_passes_args_fail(self):
		self.linux_source_mock.run_kernel = mock.Mock(return_value=[])
		with self.assertRaises(SystemExit) as e:
			kunit.main(['run'], self.linux_source_mock)
<<<<<<< HEAD
		self.assertEqual(e.exception.code, 1)
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 1)
=======
<<<<<<< HEAD
		self.assertEqual(e.exception.code, 1)
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 1)
=======
		assert type(e.exception) == SystemExit
		assert e.exception.code == 1
		assert self.linux_source_mock.build_reconfig.call_count == 1
		assert self.linux_source_mock.run_kernel.call_count == 1
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.print_mock.assert_any_call(StrContains(' 0 tests run'))

	def test_exec_raw_output(self):
		self.linux_source_mock.run_kernel = mock.Mock(return_value=[])
		kunit.main(['exec', '--raw_output'], self.linux_source_mock)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 1)
		for call in self.print_mock.call_args_list:
			self.assertNotEqual(call, mock.call(StrContains('Testing complete.')))
			self.assertNotEqual(call, mock.call(StrContains(' 0 tests run')))
<<<<<<< HEAD
=======
=======
		assert self.linux_source_mock.run_kernel.call_count == 1
		for kall in self.print_mock.call_args_list:
			assert kall != mock.call(StrContains('Testing complete.'))
			assert kall != mock.call(StrContains(' 0 tests run'))
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	def test_run_raw_output(self):
		self.linux_source_mock.run_kernel = mock.Mock(return_value=[])
		kunit.main(['run', '--raw_output'], self.linux_source_mock)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.assertEqual(self.linux_source_mock.run_kernel.call_count, 1)
		for call in self.print_mock.call_args_list:
			self.assertNotEqual(call, mock.call(StrContains('Testing complete.')))
			self.assertNotEqual(call, mock.call(StrContains(' 0 tests run')))
<<<<<<< HEAD
=======
=======
		assert self.linux_source_mock.build_reconfig.call_count == 1
		assert self.linux_source_mock.run_kernel.call_count == 1
		for kall in self.print_mock.call_args_list:
			assert kall != mock.call(StrContains('Testing complete.'))
			assert kall != mock.call(StrContains(' 0 tests run'))
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	def test_exec_timeout(self):
		timeout = 3453
		kunit.main(['exec', '--timeout', str(timeout)], self.linux_source_mock)
<<<<<<< HEAD
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', filter_glob='', timeout=timeout)
=======
<<<<<<< HEAD
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', filter_glob='', timeout=timeout)
=======
		self.linux_source_mock.run_kernel.assert_called_once_with(build_dir='.kunit', timeout=timeout)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.print_mock.assert_any_call(StrContains('Testing complete.'))

	def test_run_timeout(self):
		timeout = 3453
		kunit.main(['run', '--timeout', str(timeout)], self.linux_source_mock)
<<<<<<< HEAD
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', filter_glob='', timeout=timeout)
=======
<<<<<<< HEAD
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', filter_glob='', timeout=timeout)
=======
		assert self.linux_source_mock.build_reconfig.call_count == 1
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir='.kunit', timeout=timeout)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.print_mock.assert_any_call(StrContains('Testing complete.'))

	def test_run_builddir(self):
		build_dir = '.kunit'
		kunit.main(['run', '--build_dir=.kunit'], self.linux_source_mock)
<<<<<<< HEAD
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir=build_dir, filter_glob='', timeout=300)
=======
<<<<<<< HEAD
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir=build_dir, filter_glob='', timeout=300)
=======
		assert self.linux_source_mock.build_reconfig.call_count == 1
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir=build_dir, timeout=300)
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.print_mock.assert_any_call(StrContains('Testing complete.'))

	def test_config_builddir(self):
		build_dir = '.kunit'
		kunit.main(['config', '--build_dir', build_dir], self.linux_source_mock)
<<<<<<< HEAD
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
=======
<<<<<<< HEAD
		self.assertEqual(self.linux_source_mock.build_reconfig.call_count, 1)
=======
		assert self.linux_source_mock.build_reconfig.call_count == 1
>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

	def test_build_builddir(self):
		build_dir = '.kunit'
		kunit.main(['build', '--build_dir', build_dir], self.linux_source_mock)
		self.linux_source_mock.build_um_kernel.assert_called_once_with(False, 8, build_dir, None)

	def test_exec_builddir(self):
		build_dir = '.kunit'
		kunit.main(['exec', '--build_dir', build_dir], self.linux_source_mock)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
		self.linux_source_mock.run_kernel.assert_called_once_with(
			build_dir=build_dir, filter_glob='', timeout=300)
		self.print_mock.assert_any_call(StrContains('Testing complete.'))

	@mock.patch.object(kunit_kernel, 'LinuxSourceTree')
	def test_run_kunitconfig(self, mock_linux_init):
		mock_linux_init.return_value = self.linux_source_mock
		kunit.main(['run', '--kunitconfig=mykunitconfig'])
		# Just verify that we parsed and initialized it correctly here.
		mock_linux_init.assert_called_once_with('.kunit', kunitconfig_path='mykunitconfig')

	@mock.patch.object(kunit_kernel, 'LinuxSourceTree')
	def test_config_kunitconfig(self, mock_linux_init):
		mock_linux_init.return_value = self.linux_source_mock
		kunit.main(['config', '--kunitconfig=mykunitconfig'])
		# Just verify that we parsed and initialized it correctly here.
		mock_linux_init.assert_called_once_with('.kunit', kunitconfig_path='mykunitconfig')

<<<<<<< HEAD
=======
=======
		self.linux_source_mock.run_kernel.assert_called_once_with(build_dir=build_dir, timeout=300)
		self.print_mock.assert_any_call(StrContains('Testing complete.'))

>>>>>>> stable
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
if __name__ == '__main__':
	unittest.main()
