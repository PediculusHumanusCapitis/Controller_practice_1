Action()
{

	lr_start_transaction("UC6_RegistrationNewUsers");

	lr_start_transaction("go_to_web_tours");

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Priority", 
		"u=0, i");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_web_tours",LR_AUTO);

	lr_start_transaction("go_to_registration");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Priority", 
		"u=4");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_registration",LR_AUTO);

	lr_start_transaction("user_data_entry");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(25);

	web_submit_form("login.pl_2", 
		"Snapshot=t3.inf", 
		ITEMDATA, 
		"Name=username", "Value=alina", ENDITEM, 
		"Name=password", "Value=0070", ENDITEM, 
		"Name=passwordConfirm", "Value=0070", ENDITEM, 
		"Name=firstName", "Value=Alina", ENDITEM, 
		"Name=lastName", "Value=Konan", ENDITEM, 
		"Name=address1", "Value=Kav", ENDITEM, 
		"Name=address2", "Value=Sar", ENDITEM, 
		"Name=register.x", "Value=58", ENDITEM, 
		"Name=register.y", "Value=3", ENDITEM, 
		LAST);

	lr_end_transaction("user_data_entry",LR_AUTO);

	lr_start_transaction("click_continue");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	lr_think_time(29);

	web_image("button_next.gif", 
		"Src=/WebTours/images/button_next.gif", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("click_continue",LR_AUTO);

	lr_start_transaction("logout");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(10);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t5.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("UC6_RegistrationNewUsers",LR_AUTO);

	return 0;
}