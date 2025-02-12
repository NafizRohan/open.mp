/* Create Job */


stock bool:DoesJobExist(const Name[])
{
    mysql_format(db, DB_query, sizeof(DB_query), "SELECT COUNT(*) FROM Job WHERE Name = '%e'", Name);
    new Cache:result = mysql_query(db, DB_query);
    if (cache_get_row_count(result) > 0)
    {
        cache_delete(result);
        return true;
    }
    cache_delete(result);
    return false;
}



stock CreateJob(playerid, const Name[] = "NULL", Type, skin, Salary, PlayerID = -1, Float:PosX = 0.0, Float:PosY = 0.0, Float:PosZ = 0.0)
{
    new OwnerID, Owner[MAX_PLAYER_NAME + 1], jobid;
    if(IsPlayerConnected(PlayerID))
    {
        OwnerID = gPlayerData[PlayerID][pID];
        strcat(Owner, gPlayerData[PlayerID][pName]);
    }
    else
    {
        OwnerID = 0;
        strcat(Owner, "Govt.");
    }
    if(strcmp(Name, "NULL", true) == 0) return SEM(playerid, "Oops! You forgot to enter a job name.");
    if(DoesJobExist(Name)) return SEM(playerid, "Oops! This job already exists.");
    if(Type < 1 || Type > 2) return SEM(playerid, "Oops! Invalid job type.");
    if(skin < 0 || skin > 312) return SEM(playerid, "Oops! Invalid skin ID.");
    if(Salary < 100) return SEM(playerid, "Oops! Invalid salary.");

    GetPlayerPos(playerid, PosX, PosY, PosZ);
    for(new i = 0; i != MAX_JOBS; i++)
    {
        if(!gJobData[i][jExists])
        {
            gJobData[i][jExists] = 1;
            strcat(gJobData[i][jName], Name);
            gJobData[i][jType] = Type;
            gJobData[i][jSkin] = skin;
            gJobData[i][jSalary] = Salary;
            gJobData[i][jOwnerID] = OwnerID;
            strcat(gJobData[i][jOwner], Owner);
            gJobData[i][jPos][0] = PosX;
            gJobData[i][jPos][1] = PosY;
            gJobData[i][jPos][2] = PosZ;
            jobid = i;
            break;
        }
        else{
            if(i == MAX_JOBS - 1) return SEM(playerid, "Oops! Maximum job limit reached.");
        }
    }
    mysql_format(db, DB_query, sizeof(DB_query), "INSERT INTO Job (Name, Type, Skin, Salary, OwnerID, Owner, PosX, PosY, PosZ) VALUES ('%e', %d, %d, %d, %d, '%e', %f, %f, %f)", Name, Type, skin, Salary, OwnerID, Owner, PosX, PosY, PosZ);
    mysql_tquery(db, DB_query, "OnJobCreated", "ii", playerid, jobid);
    return true;
}

CB: OnJobCreated(playerid, jobid)
{
    gJobData[jobid][jID] = cache_insert_id();
    new string[128];
    format(string, sizeof(string), "Job created successfully. ID: %d", jobid);
    SEM(playerid, string);
    ReloadJob(jobid);
    return 1;
}
 