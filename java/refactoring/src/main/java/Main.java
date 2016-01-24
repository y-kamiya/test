class Main {

    public static void main(String[] args) {

        Movie movie1 = new Movie("regular", Movie.REGULAR);
        Movie movie2 = new Movie("new_release", Movie.NEW_RELEASE);
        Movie movie3 = new Movie("childrens", Movie.CHILDRENS);

        Rental rental1 = new Rental(movie1, 1);
        Rental rental2 = new Rental(movie2, 2);
        Rental rental3 = new Rental(movie3, 3);

        Customer mark = new Customer("Mark");
        mark.addRental(rental1);
        mark.addRental(rental2);
        mark.addRental(rental3);

        String output = mark.statement();
        System.out.println(output);
    }
}
