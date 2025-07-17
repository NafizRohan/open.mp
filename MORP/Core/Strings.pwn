new logstr[128];

stock bool:findsymbol(const string[]) {
    for (new i = 0; i < strlen(string); i++) {
        if (!((string[i] >= 'a' && string[i] <= 'z') || 
              (string[i] >= 'A' && string[i] <= 'Z') ||  
              (string[i] >= '0' && string[i] <= '9'))) return true;  

    }
    return false;
}

stock bool:isValidUnderscoreString(const string[]) {
    new bool:hasUnderscore = false;

    for (new i = 0; i < strlen(string); i++) {
        if (string[i] == '_') {
            hasUnderscore = true;
        }
        else if ((string[i] < 'A' || string[i] > 'Z') && (string[i] < 'a' || string[i] > 'z')) {
            return false;
        }
    }
    return hasUnderscore;
}

stock ReturnString(value[]) {
	new str[128];
	format(str, sizeof(str), "%s", value);
	return str;
}
