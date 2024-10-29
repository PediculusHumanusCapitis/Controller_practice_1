Action()
{
	int i;
	int count;

	lr_start_transaction("UC2_SearchTicket");
	
	GoToHomePage();
	Login();

	lr_start_transaction("go_to_flights");
	
	web_reg_find("Text=Find Flight",LAST);
	
	
	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	
	web_reg_save_param_ex("ParamName=NotDefoiltCity",
	                      "LB=<option value=\"",
	                      "RB=\">",
	                      "Ordinal=ALL",
	                      LAST);
	
	web_reg_save_param_ex("ParamName=DefoiltCity",
	                      "LB=\"selected\" value=\"",
	                      "RB=\">",
	                      "Ordinal=ALL",
	                      LAST);
	
	
	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t5.inf", 
		LAST);


	lr_end_transaction("go_to_flights",LR_AUTO);
	lr_think_time(5);

	lr_start_transaction("find_flight");
	
	
	lr_save_string(lr_paramarr_idx("DefoiltCity", 1), "AllCities");

	count = lr_paramarr_len("NotDefoiltCity");
	
	for (i = 1; i <= count; i++) {
		char* currentCity = lr_paramarr_idx("NotDefoiltCity", i);
    	if (strstr(lr_eval_string("{AllCities}"), currentCity) == NULL) {
            lr_param_sprintf("AllCities", "%s,%s", lr_eval_string("{AllCities}"), currentCity);
        }
	}
lr_save_param_regexp(lr_eval_string("{AllCities}"),
                     strlen(lr_eval_string("{AllCities}")),
                     "RegExp=([^,]+)",
                     "Ordinal=All",
                     "ResultParam=CityArray",
                     LAST);

	lr_save_string(lr_paramarr_random("CityArray"),"DepartureCity");
	
	lr_save_string(lr_paramarr_random("CityArray"), "ArrivalrCity");
	
	while(strcmp(lr_eval_string("{DepartureCity}"), lr_eval_string("{ArrivalrCity}")) == 0){
		lr_save_string(lr_paramarr_random("CityArray"), "ArrivalrCity");
	}

	

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
		web_reg_save_param_ex("ParamName=AllOutboundFlight",
	                      "LB=Flight\" value=\"",
	                      "RB=\"",
	                      "Ordinal=ALL",
	                      LAST);


	
	

	web_reg_find("Text=departing from <B>{DepartureCity}</B> to <B>{ArrivalrCity}</B>",LAST);
	
	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={DepartureCity}", ENDITEM, 
		"Name=departDate", "Value={DepartDate}", ENDITEM, 
		"Name=arrive", "Value={ArrivalrCity}", ENDITEM, 
		"Name=returnDate", "Value={ReturnDate}", ENDITEM, 
		"Name=numPassengers", "Value={NumPass}", ENDITEM, 
		"Name=seatPref", "Value={SeatPref}", ENDITEM, 
		"Name=seatType", "Value={SeatType}", ENDITEM, 
		"Name=findFlights.x", "Value=61", ENDITEM, 
		"Name=findFlights.y", "Value=10", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("find_flight",LR_AUTO);
	lr_think_time(5);
	
	lr_start_transaction("choosing a flight");
	lr_save_string(lr_paramarr_random("AllOutboundFlight"),"OutboundFlight");
	
	web_reg_find("Text=Payment Details",LAST);
	
	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={OutboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value={NumPass}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={SeatType}", ENDITEM, 
		"Name=seatPref", "Value={SeatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=72", ENDITEM, 
		"Name=reserveFlights.y", "Value=12", ENDITEM, 
		LAST);

	lr_end_transaction("choosing a flight",LR_AUTO);
	lr_think_time(5);
	
	
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

	//Logout();

	lr_end_transaction("UC2_SearchTicket",LR_AUTO);

	return 0;
}