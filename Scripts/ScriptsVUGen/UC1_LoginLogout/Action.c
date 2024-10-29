Action()
{

	lr_start_transaction("UC1_LoginLogout");

	lr_start_transaction("go_to_web_tours");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_header("Sec-Fetch-Dest", 
		"document");

	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_header("Priority", 
		"u=0, i");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("Priority", 
		"u=4");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_url("header.html", 
		"URL=http://localhost:1080/WebTours/header.html", 
		"Resource=0", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=images/hp_logo.png", ENDITEM, 
		"Url=images/webtours.png", ENDITEM, 
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_web_tours",LR_AUTO);
	lr_think_time(3);
	lr_start_transaction("login");
	
	web_reg_find("Text=Welcome, <b>{UserLogin}</b>, to the Web Tours",LAST);
	
	
	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");



	web_submit_form("login.pl", 
		"Snapshot=t4.inf", 
		ITEMDATA, 
		"Name=username", "Value={UserLogin}", ENDITEM, 
		"Name=password", "Value={UserPassword}", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);
	lr_think_time(3);
	lr_start_transaction("go_to_flights");
	
	web_reg_find("Text=Find Flight",LAST);
	
	
	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	
	
	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t5.inf", 
		LAST);


	lr_end_transaction("go_to_flights",LR_AUTO);
	lr_think_time(3);
	lr_start_transaction("go_to_itinerary");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");


	
//	web_reg_save_param_ex("ParamName=FlightID",
//	                      "LB=flightID\" value=\"",
//	                      "RB=\"",
//	                      "Ordinal=ALL",
//	                      LAST);
//	
//    web_reg_save_param_ex("ParamName=Cgifields",
//	                      "LB=cgifields\" value=\"",
//	                      "RB=\"",
//	                      "Ordinal=ALL",
//	                      LAST);
    
	web_reg_find("Text=<B>{UserFName} {UserLName}",LAST);
	web_reg_find("Text=Flight Transaction Summary",LAST);
	
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t38.inf", 
		"Mode=HTML", 
		LAST);
    

	lr_end_transaction("go_to_itinerary",LR_AUTO);
	lr_think_time(5);

	lr_start_transaction("logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	
	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");


	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t5.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	lr_think_time(3);

	lr_end_transaction("UC1_LoginLogout",LR_AUTO);

	return 0;
}