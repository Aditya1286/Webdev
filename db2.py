from sqlalchemy import create_engine, Column, Integer, String, func
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

# Define the base class for the model
Base = declarative_base()

# Define the Item model
class Item(Base):
    __tablename__ = 'items'

    id = Column(Integer, primary_key=True)
    name = Column(String, unique=False)
    description = Column(String)

    def __repr__(self):
        return f"<Item(id={self.id}, name={self.name}, description={self.description})>"

# Set up the database connection (example with SQLite)
DATABASE_URI = 'sqlite:///example.db'  # Example URI (for SQLite, modify as needed)
engine = create_engine(DATABASE_URI)
Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()

# Function to remove duplicates based on 'name' field
def remove_duplicates():
    # Fetch items grouped by name and find duplicates (having more than 1 occurrence)
    items = session.query(Item.name, func.count(Item.id).label('count')).group_by(Item.name).having(func.count(Item.id) > 1).all()

    # For each duplicate item group, keep the first one and delete the rest
    for name, _ in items:
        duplicate_items = session.query(Item).filter(Item.name == name).all()
        if len(duplicate_items) > 1:
            for item in duplicate_items[1:]:
                session.delete(item)  # Delete duplicate items

    # Commit changes to the database
    session.commit()
    print("Duplicates removed successfully.")

# Call the function to remove duplicates
if __name__ == "__main__":
    remove_duplicates()
