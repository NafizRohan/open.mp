// Global string buffer for logging purposes
new logstr[128];

// Checks if the string contains any non-alphanumeric character
stock bool:findsymbol(const string[]) {
    // Loop through each character in the string
    for (new i = 0; i < strlen(string); i++) {
        // If the character is not a letter or digit, return true
        if (!((string[i] >= 'a' && string[i] <= 'z') || 
              (string[i] >= 'A' && string[i] <= 'Z') ||  
              (string[i] >= '0' && string[i] <= '9'))) return true;  
    }
    // Return false if all characters are alphanumeric
    return false;
}

// Checks if the string contains at least one underscore and only letters and underscores
stock bool:isValidUnderscoreString(const string[]) {
    new bool:hasUnderscore = false;

    // Loop through each character in the string
    for (new i = 0; i < strlen(string); i++) {
        if (string[i] == '_') {
            hasUnderscore = true; // Mark if underscore is found
        }
        // If character is not a letter or underscore, return false
        else if ((string[i] < 'A' || string[i] > 'Z') && (string[i] < 'a' || string[i] > 'z')) {
            return false;
        }
    }
    // Return true only if at least one underscore was found
    return hasUnderscore;
}

// Returns a formatted string copy of the input value
stock ReturnString(value[]) {
    new str[128];
    format(str, sizeof(str), "%s", value); // Copy value into str
    return str;
}
