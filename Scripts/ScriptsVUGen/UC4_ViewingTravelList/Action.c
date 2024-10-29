Action()
{

	lr_start_transaction("UC4_ViewingTravelList");

	GoToHomePage();
	Login();
	lr_start_transaction("go_to_itinerary");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(14);
	
	web_reg_find("Text=<B>{UserFName} {UserLName}",LAST);
	web_reg_find("Text=Flight Transaction Summary",LAST);
	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t9.inf", 
		LAST);

	lr_end_transaction("go_to_itinerary",LR_AUTO);

	Logout();

	lr_end_transaction("UC4_ViewingTravelList",LR_AUTO);

	return 0;
}