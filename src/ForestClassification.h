/*-------------------------------------------------------------------------------
 This file is part of Ranger.

 Ranger is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Ranger is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Ranger. If not, see <http://www.gnu.org/licenses/>.

 Written by: Roman Hornung, Marvin N. Wright
 #-------------------------------------------------------------------------------*/

#ifndef FORESTCLASSIFICATION_H_
#define FORESTCLASSIFICATION_H_

#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "globals.h"
#include "Forest.h"

class ForestClassification: public Forest {
public:
  ForestClassification();
  virtual ~ForestClassification();

  void loadForest(size_t dependent_varID, size_t num_trees,
      std::vector<std::vector<std::vector<size_t>> >& forest_child_nodeIDs,
      std::vector<std::vector<size_t>>& forest_split_varIDs, std::vector<std::vector<double>>& forest_split_values,
      std::vector<double>& class_values, std::vector<bool>& is_ordered_variable);

  const std::vector<double>& getClassValues() const {
    return class_values;
  }

protected:
  void initInternal(std::string status_variable_name);
  void growInternal();
  void allocatePredictMemory();
  void predictInternal(size_t sample_idx);
  void computePredictionErrorInternal();
  void writeOutputInternal();
  void writeConfusionFile();
  void writePredictionFile();
  void saveToFileInternal(std::ofstream& outfile);
  void loadFromFileInternal(std::ifstream& infile);

  // Classes of the dependent variable and classIDs for responses
  std::vector<double> class_values;
  std::vector<uint> response_classIDs;
  std::vector<std::vector<size_t>> sampleIDs_per_class;

  // Table with classifications and true classes
  std::map<std::pair<double, double>, size_t> classification_table;

private:
  DISALLOW_COPY_AND_ASSIGN(ForestClassification);
};

#endif /* FORESTCLASSIFICATION_H_ */
