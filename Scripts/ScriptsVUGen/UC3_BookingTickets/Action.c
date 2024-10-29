Action()
{
	int i;
	int j;
	int count;
	char* outboundFlight;
	char encodedFlight[1024] = "";
	
	lr_start_transaction("UC3_BookingTickets");
	
	GoToHomePage();
	Login();
	lr_start_transaction("go_to_flights");
	
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

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	web_reg_find("Text=Find Flight",LAST);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_flights",LR_AUTO);
	
	lr_think_time(3);

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
	                     "RegExp=(.*?)(?:,|$)",
	                     "Ordinal=All",
	                     "ResultParam=CityArray",
	                     LAST);

	lr_save_string(lr_paramarr_random("CityArray"),"DepartureCity");
	
	lr_save_string(lr_paramarr_random("CityArray"), "ArrivalrCity");
	
	while(strcmp(lr_eval_string("{DepartureCity}"), lr_eval_string("{ArrivalrCity}")) == 0){
		lr_save_string(lr_paramarr_random("CityArray"), "ArrivalrCity");
	}

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
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
		"Snapshot=t7.inf", 
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
	
	lr_think_time(4);	
	
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
	
	lr_think_time(3);
	
	lr_start_transaction("booking");
	
	lr_save_string("", "BodyRequest");
	
	lr_param_sprintf("BodyRequest",
	                 "%sfirstName=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{BuersFirstName}"));
	
	lr_param_sprintf("BodyRequest",
	                 "%slastName=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{BuersLastName}"));
	
	lr_param_sprintf("BodyRequest",
	                 "%saddress1=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{Street}"));
	
	lr_param_sprintf("BodyRequest",
	                 "%saddress2=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{City}"));
	
	lr_param_sprintf("BodyRequest",
	                 "%spass1=%s+%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{BuersFirstName}"),
	                 lr_eval_string("{BuersLastName}"));
	
	count = atoi(lr_eval_string("{NumPass}"));
	
	if(count > 1){
		for(i=2 ; i<=count; i++){
			lr_output_message("c_buffer: %d",i);
			lr_param_sprintf("BodyRequest",
			                 "%spass%d=%s+%s&",
			                 lr_eval_string("{BodyRequest}"),
			                 i,
			                 lr_eval_string("{FNOtherPass}"),
			                 lr_eval_string("{LNOtherPass}"));
		}
	}
	lr_param_sprintf("BodyRequest",
	                 "%screditCard=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{CreditCard}"));
	lr_param_sprintf("BodyRequest",
	                 "%sexpDate=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{ExpDate}"));
	lr_param_sprintf("BodyRequest",
	                 "%soldCCOption=&numPassengers=%d&",
	                 lr_eval_string("{BodyRequest}"),
	                 count);
	
	lr_param_sprintf("BodyRequest",
	                 "%sseatType=%s&seatPref=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{SeatType}"),
	                 lr_eval_string("{SeatPref}"));
	
	outboundFlight = lr_eval_string("{OutboundFlight}");
     i = 0;
     j = 0;
    for (i = 0; outboundFlight[i] != '\0'; i++) {
        if (outboundFlight[i] == ';') {
            strcat(encodedFlight, "%3B");
            j += 3;  
     	}else if (outboundFlight[i] == '/') {
            strcat(encodedFlight, "%2F");
            j += 3;
        }else {
            encodedFlight[j] = outboundFlight[i];
            encodedFlight[j + 1] = '\0';
            j++;
        }
    }
     
	lr_save_string(encodedFlight, "OutboundFlightEncoded");
	
	lr_param_sprintf("BodyRequest",
	                 "%soutboundFlight=%s&",
	                 lr_eval_string("{BodyRequest}"),
	                 lr_eval_string("{OutboundFlightEncoded}"));
	
	lr_param_sprintf("BodyRequest",
	                 "%sadvanceDiscount=0&returnFlight=&JSFormSubmit=off&buyFlights.x=59&buyFlights.y=12&.cgifields=saveCC",
	                 lr_eval_string("{BodyRequest}"));
	
	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_reg_find("Text=Thank you for booking through Web Tours",LAST);
	web_reg_find("Text=<b>{BuersFirstName}{BuersLastName}'s Flight Invoice</b>",LAST);
	
	web_custom_request("reservations.pl_3", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		"Body={BodyRequest}", 
		LAST);
	
	lr_end_transaction("booking",LR_AUTO);
	lr_think_time(5);
	
	Logout();

	lr_end_transaction("UC3_BookingTickets",LR_AUTO);

	return 0;
}