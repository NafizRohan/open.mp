CB:LoadJob()
{
    new rows, string[128];
    cache_get_row_count(rows);
    if(rows){
        for(new i = 0; i < rows; i++){
            cache_get_value_int(i, "JobID", gJobData[i][jID]);
            cache_get_value_name(i, "JobName", gJobData[i][jName]);
            cache_get_value_int(i, "JobType", gJobData[i][jType]);
            cache_get_value_int(i, "JobSkin", gJobData[i][jSkin]);
            cache_get_value_int(i, "JobSalary", gJobData[i][jSalary]);
            cache_get_value_int(i, "JobOwnerID", gJobData[i][jOwnerID]);
            cache_get_value_int(i, "JobExists", gJobData[i][jExists]);
            cache_get_value_float(i, "JobPosX", gJobData[i][jPos][0]);
            cache_get_value_float(i, "JobPosY", gJobData[i][jPos][1]);
            cache_get_value_float(i, "JobPosZ", gJobData[i][jPos][2]);
            cache_get_value_name(i, "JobOwner", gJobData[i][jOwner]);

            if(gJobData[i][jExists]){
                format(string, sizeof(string), ""COLOR_YELLOW"%s(%d)\n"COLOR_WHITE"Salary: "COLOR_YELLOW"$%d\n"COLOR_WHITE"Owner: "COLOR_YELLOW"%s\n",
                    gJobData[i][jName],
                    gJobData[i][jID],
                    gJobData[i][jSalary],
                    gJobData[i][jOwner]);
                if(IsValidDynamicPickup(gJobData[i][jPickup])){
                    DestroyDynamicPickup(gJobData[i][jPickup]);
                }
                if(IsValidDynamic3DTextLabel(gJobData[i][jLabel])){
                    DestroyDynamic3DTextLabel(gJobData[i][jLabel]);
                }
                gJobData[i][jLabel] = CreateDynamic3DTextLabel(string, SERVER_COLOR, gJobData[i][jPos][0], gJobData[i][jPos][1], gJobData[i][jPos][2], 20.0, .worldid = -1, .interiorid = -1);
                gJobData[i][jPickup] = CreateDynamicPickup(1274, 23, gJobData[i][jPos][0], gJobData[i][jPos][1], gJobData[i][jPos][2], -1, 0, 0, 0);
            }
        }
    }
}
hook OnGameModeInit()
{
    mysql_tquery(db, "SELECT * FROM `jobs`", "LoadJob");
    return 1;
}