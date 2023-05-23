#pragma once
#include "service.h"
#include "ServiceCos.h"
class Console {
private:
	Service& service;
	ServiceCos& serviceCOS;
	void console_add();
	void console_del();
	void console_mod();
	void console_search() const;
	void console_print_all() const;
	void console_filter() const;
	void console_sort() const;
	void console_print_menu() const;
	void console_raport() const;
	void console_undo();

	void console_print_cos() const;
	void console_add_cos();
	void console_clear_cos();
	void console_generate_cos();
	void console_export_cos();

public:
	Console() = delete;
	Console(Service& srv, ServiceCos& srvc) : service{ srv }, serviceCOS{ srvc } {}
	Console(const Console& other) = delete;
	void runConsole();
};