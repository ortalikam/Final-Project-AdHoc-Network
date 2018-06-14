import csv

data=[['000','001','010'],['001','111','110']]
with open('db.csv', 'wb') as csvfile:
    #spamwriter = csv.writer(csvfile, delimiter=' ',
    #                        quotechar='|', quoting=csv.QUOTE_MINIMAL)
    #spamwriter.writerows(list)
    #for data in list
    #    spamwriter.writerow(['Spam'] * 5 + ['Baked Beans'])

    fieldnames = ['father', 'son','son']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()
    for list in data:
        writer.writerow({'father': list[0], 'son':  list[1], 'son':  list[2]})


