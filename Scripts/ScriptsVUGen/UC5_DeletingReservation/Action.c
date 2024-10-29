Action()
{
	int i;
	int count;

	lr_start_transaction("UC5_DeletingReservation");
	GoToHomePage();
	Login();
	lr_start_transaction("go_to_itinerary");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_reg_save_param_ex("ParamName=FlightID",
	                      "LB=flightID\" value=\"",
	                      "RB=\"",
	                      "Ordinal=ALL",
	                      LAST);
	
    web_reg_save_param_ex("ParamName=Cgifields",
	                      "LB=cgifields\" value=\"",
	                      "RB=\"",
	                      "Ordinal=ALL",
	                      LAST);
    
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

	lr_start_transaction("delete_reservation");

	web_add_header("Origin", 
		"http://localhost:1080");
	
	lr_save_string("", "BodyRequest");
	
	
	count = atoi(lr_eval_string("{CountDeletions}"));
	
	if(count>atoi(lr_eval_string("{FlightID_count}"))){
		count=atoi(lr_eval_string("{FlightID_count}"));
	   }
		
	for(i=1; i<=count; i++){
		lr_param_sprintf("BodyRequest",
		                 "%s%d=on&",
		                 lr_eval_string("{BodyRequest}"),
		                 i);
	}

    for (i=1; i<=atoi(lr_eval_string("{FlightID_count}")); i++)
    {
        lr_param_sprintf("BodyRequest",
    	                 "%sflightID=%s&",
    	                 lr_eval_string("{BodyRequest}"),
    	                 lr_paramarr_idx("FlightID",i));
    }
    
    lr_param_sprintf("BodyRequest",
                     "%sremoveFlights.x=50&removeFlights.y=5",
                     lr_eval_string("{BodyRequest}"));

    for (i=1;i<=atoi(lr_eval_string("{Cgifields_count}"));i++)
    {
        lr_param_sprintf("BodyRequest",
    	                 "%s&.cgifields=%s",
    	                 lr_eval_string("{BodyRequest}"),
    	                 lr_paramarr_idx("Cgifields",i));
    }
    
    
    web_reg_find("Text=<b>A total of {FlightID_count} scheduled flights.", "Fail=Found", LAST);
	web_reg_find("Text=>Itinerary<",LAST);
	
	web_custom_request("itinerary.pl", 
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		"Body={BodyRequest}", 
		LAST);

	lr_end_transaction("delete_reservation",LR_AUTO);
	lr_think_time(5);

	Logout();

	lr_end_transaction("UC5_DeletingReservation",LR_AUTO);

	return 0;
}