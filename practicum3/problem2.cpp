#include <iostream>

using namespace std;


class Movie {
    public:
        Movie() {
            title = "";
            studio = "";
            tickets = 0;
        }

        Movie(string initialTitle, string initialStudio, int initialTickets) {
            title = initialTitle;
            studio = initialStudio;
            tickets = initialTickets;
        }


        // Getters
        string getTitle() {
            return title;
        }

        string getStudio() {
            return studio;
        }

        int getTickets() {
            return tickets;
        }

        // Setters
        void setTitle(string newTitle) {
            title = newTitle;
        }

        void setStudio(string newStudio) {
            studio = newStudio;
        }

        void setTickets(int newTickets) {
            tickets = newTickets;
        }

        double grossRevenue(double price) {
            double revenue = price * tickets;
            return revenue;
        }


    private:
        string title = "";
        string studio = "";
        int tickets = 0;
};