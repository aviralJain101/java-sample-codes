import string
from collections import Counter
from datetime import datetime
from typing import List, Dict

# Sample data for demonstration
reviews = [
    {
        "id": 1,
        "rating": 5,
        "review": "Great app! Very useful and easy to use.",
        "date": "2024-01-15"
    },
    {
        "id": 2,
        "rating": 4,
        "review": "Good functionality, but could use more features.",
        "date": "2024-02-20"
    },
    {
        "id": 3,
        "rating": 3,
        "review": "Average experience. The app crashes occasionally.",
        "date": "2024-01-25"
    },
    # Add more reviews as needed
]

def analyze_reviews(reviews: List[Dict]) -> None:
    if not reviews:
        print("No reviews to analyze.")
        return

    # Task 1: Calculate the average rating
    total_rating = 0
    for review in reviews:
        rating = review.get('rating', 0)
        if isinstance(rating, int) and 1 <= rating <= 5:
            total_rating += rating
        else:
            print(f"Invalid rating '{rating}' in review ID {review.get('id')}. Skipping.")
    average_rating = total_rating / len(reviews)
    print(f"Average Rating: {average_rating:.2f}")

    # Task 2: Identify the most common words
    all_words = []
    translator = str.maketrans('', '', string.punctuation)
    for review in reviews:
        review_text = review.get('review', '')
        # Remove punctuation
        cleaned_text = review_text.translate(translator)
        words = cleaned_text.split()
        all_words.extend(words)
    
    word_counts = Counter(all_words)
    most_common_words = word_counts.most_common(10)  # Top 10 common words
    print("\nMost Common Words:")
    for word, count in most_common_words:
        print(f"{word}: {count}")

    # Task 3: Find the month with the most reviews
    month_counts = Counter()
    for review in reviews:
        date_str = review.get('date', '')
        try:
            date_obj = datetime.strptime(date_str, "%Y-%m-%d")
            month = date_obj.strftime("%B %Y")  # e.g., "January 2024"
            month_counts[month] += 1
        except ValueError:
            print(f"Invalid date format '{date_str}' in review ID {review.get('id')}. Skipping.")
    
    if month_counts:
        most_common_month, count = month_counts.most_common(1)[0]
        print(f"\nMonth with Most Reviews: {most_common_month} ({count} reviews)")
    else:
        print("\nNo valid dates found in reviews.")

# Run the analysis
analyze_reviews(reviews)
