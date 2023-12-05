/* PHOENIX !*/

//For the movie table
#include <iostream>
#include <string>
#include <stdlib.h>

/*Drivers for SQL*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main()
{
    cout << endl;

    try {

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *prep_stmt;

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://deltona.birdnest.org:3306", "my.weaverh3", "r780t0b1");
    /* Connect to the MySQL test database */
    con->setSchema("my_weaverh3_groupProgrammingProject");

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT MovieID AS _column FROM Views_Movie");
    while (res->next()) {
        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("_column") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column data by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
    }

    string actionType;
    cout << "input what action to perform: (C for Create, R for Read, U for Update, or D for delete) " << endl;
    cin >> actionType;

    if (actionType == "C" || actionType == "c" ) {

        int movieID, profileID, pctComp;
        cout << "Enter movie ID ";
        cin >> movieID;
        cout << "Enter the profile ID ";  
        cin >> profileID;
        cout << "Enter the percent complete " << endl;  
        cin >> pctComp;
    
        prep_stmt = con->prepareStatement("INSERT INTO Views_Movie (MovieID, ProfileID, PercentComplete) VALUES (?, ?, ?)");
        prep_stmt->setInt(1,movieID);
        prep_stmt->setInt(2,profileID);
        prep_stmt->setInt(3,pctComp);
        prep_stmt->execute();

        delete prep_stmt;
        //res = stmt->executeQuery("SELECT Name AS _column FROM Movie"); 
    }

    else if (actionType == "R" || actionType == "r") {
        string columnName;
        cout << "Enter column name ";
        cin >> columnName;

        res = stmt->executeQuery("SELECT " + columnName + " AS _column FROM Views_Movie"); 
    }

    else if (actionType == "U" || actionType == "u") {
        
        string columnName;
        columnName = "PercentComplete";
        cout << "Enter an integer that is the new value for PercentComplete ";
        int updatedVal, movieID, profileID;
        cin >> updatedVal;
        cout << "Enter the id number of the Movie ";
        cin >> movieID;
        cout << "Enter the id number of the Profile watching the movie ";
        cin >> profileID;

        prep_stmt = con->prepareStatement("UPDATE Views_Movie SET " + columnName + " = ? WHERE ProfileID = ? AND MovieID = ?");
        prep_stmt->setInt(1,updatedVal);
        prep_stmt->setInt(2,profileID);
        prep_stmt->setInt(3,movieID);
        prep_stmt->execute();

        delete prep_stmt; 

    }

    else if (actionType == "D" || actionType == "d") {
        //DELETE FROM table_name WHERE condition;
        int mid, pid;
        cout << "Enter the movieid of the movie you're trying to delete a record from " << endl;
        cin >> mid;
        cout << "Enter the profileid of the movie you're trying to delete a record from " << endl;
        cin >> pid;

        prep_stmt = con->prepareStatement("DELETE FROM Views_Movie WHERE ProfileID = ? AND MovieID = ?");
        prep_stmt->setInt(1,pid);
        prep_stmt->setInt(2,mid);
        prep_stmt->execute();

        delete prep_stmt; 

    }

    else {
        cout << "Error: you did not enter what action you would like to perform";
    }
    
    while (res->next()) {
        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("_column") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column data by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
    }

    //DELETES FOR POINTERS DONT MESS W THIS!!!!!!!!!!!!:D
    delete res;
    delete stmt;
    delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;

    return 0;
    
}