Action()
{
	lr_start_transaction("UC6_RegistrationNewUsers");

	GoToHomePage();

	lr_start_transaction("go_to_registration");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Priority", 
		"u=4");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");
	web_reg_find("Text=Customer Profile",LAST);
	
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
	web_reg_find("Text=Thank you, <b>{UserLogin}</b>, for registering",LAST);
	web_submit_form("login.pl_2", 
		"Snapshot=t3.inf", 
		ITEMDATA, 
		"Name=username", "Value={UserLogin}", ENDITEM, 
		"Name=password", "Value={UserPassword}", ENDITEM, 
		"Name=passwordConfirm", "Value={UserPassword}", ENDITEM, 
		"Name=firstName", "Value={FirstName}", ENDITEM, 
		"Name=lastName", "Value={LastName}", ENDITEM, 
		"Name=address1", "Value={Street}", ENDITEM, 
		"Name=address2", "Value={City}", ENDITEM, 
		"Name=register.x", "Value=58", ENDITEM, 
		"Name=register.y", "Value=3", ENDITEM, 
		LAST);

	lr_end_transaction("user_data_entry",LR_AUTO);

	lr_start_transaction("click_continue");
	web_reg_find("Text=Welcome, <b>{UserLogin}</b>, to the Web Tours",LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	lr_think_time(29);

	web_image("button_next.gif", 
		"Src=/WebTours/images/button_next.gif", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("click_continue",LR_AUTO);

	Logout();

	lr_end_transaction("UC6_RegistrationNewUsers",LR_AUTO);

	return 0;
}